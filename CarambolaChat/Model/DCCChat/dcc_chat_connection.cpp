
#include "precomp.h"
#include "dcc_chat_connection.h"

DCCChatConnection::DCCChatConnection(const std::string &local_nick, const std::string &remote_nick, const uicore::SocketName &socket_name)
: local_nick(local_nick), remote_nick(remote_nick), socket_name(socket_name), is_server(false)
{
}

DCCChatConnection::~DCCChatConnection()
{
	disconnect();
}

void DCCChatConnection::connect()
{
	is_server = false;
	thread = std::thread(&DCCChatConnection::worker_main, this);
}

void DCCChatConnection::offer()
{
	is_server = true;
	thread = std::thread(&DCCChatConnection::worker_main, this);

	std::unique_lock<std::mutex> lock(mutex);
	started_event.wait(lock, [&]() { return started_flag; });
}

void DCCChatConnection::disconnect()
{
	std::unique_lock<std::mutex> lock(mutex);
	stop_flag = true;
	lock.unlock();
	change_event.notify();
	thread.join();
}

void DCCChatConnection::send_line(const IRCText &text)
{
	std::unique_lock<std::mutex> lock(mutex);
	send_queue.push_back(Message(Message::type_text, text.to_raw()));
	lock.unlock();
	change_event.notify();
}

void DCCChatConnection::process()
{
	std::vector<Message> received_messages;
	std::unique_lock<std::mutex> lock(mutex);
	received_messages.swap(receive_queue);
	lock.unlock();

	for (size_t i = 0; i < received_messages.size(); i++)
	{
		switch (received_messages[i].type)
		{
		case Message::type_system:
			sig_system_text(received_messages[i].text);
			break;
		case Message::type_text:
			{
				IRCRawString text = received_messages[i].text;
				if (text.length() >= 2 && text.substr(text.length() - 2, 2) == "\r\n")
					text = text.substr(0, text.length() - 2);
				else if (text.length() >= 1 && text[text.length() - 1] == '\n')
					text = text.substr(0, text.length() - 1);
				sig_text_line(IRCText::from_raw(text));
			}
			break;
		case Message::type_disconnect:
			sig_disconnected(received_messages[i].text);
			break;
		}
	}
}

void DCCChatConnection::worker_main()
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		started_flag = true;
		started_event.notify_all();
		lock.unlock();
	}

	try
	{
		std::unique_lock<std::mutex> lock(mutex);
		uicore::TCPConnectionPtr connection;
		if (is_server)
		{
			queue_system(uicore::string_format("Started listening on port %1", socket_name.port()));

			auto listen = uicore::TCPListen::listen(socket_name);

			while (true)
			{
				if (stop_flag)
				{
					queue_disconnected(IRCRawString());
					return;
				}

				uicore::SocketName end_point;
				connection = listen->accept(end_point);
				if (connection)
					break;

				uicore::NetworkEvent *events[] = { listen.get() };
				change_event.wait(lock, 1, events);
			}

			uicore::SocketName remote_name = connection->remote_name();

			lock.unlock();
			try
			{
				queue_system(uicore::string_format("Accepted connection from %1 port %2", remote_name.lookup_hostname(), remote_name.port()));
			}
			catch (uicore::Exception &)
			{
				queue_system(uicore::string_format("Accepted connection from %1 port %2", remote_name.address(), remote_name.port()));
			}
			lock.lock();
		}
		else
		{
			lock.unlock();
			try
			{
				queue_system(uicore::string_format("Connecting to %1 port %2", socket_name.lookup_hostname(), socket_name.port()));
			}
			catch (uicore::Exception &)
			{
				queue_system(uicore::string_format("Connecting to %1 port %2", socket_name.address(), socket_name.port()));
			}
			connection = uicore::TCPConnection::connect(socket_name);
			lock.lock();
		}

		IRCRawString read_line, write_line;
		IRCRawString::size_type write_pos = 0;

		while (!stop_flag)
		{
			if (!read_connection_data(*connection, read_line))
				break;

			if (!write_connection_data(write_line, write_pos, *connection))
				break;

			uicore::NetworkEvent *events[] = { connection.get() };
			change_event.wait(lock, 1, events);
		}

		queue_disconnected(IRCRawString());
	}
	catch (uicore::Exception &e)
	{
		std::unique_lock<std::mutex> lock(mutex);
		queue_disconnected(e.message);
	}
}

bool DCCChatConnection::read_connection_data(uicore::TCPConnection &connection, IRCRawString &read_line)
{
	while (true)
	{
		char buffer[16 * 1024];
		int data_read = connection.read(buffer, 16 * 1024);
		if (data_read == -1)
			return true;
		if (data_read == 0) // EOF from server
			return false;

		int start_pos = 0;
		for (int i = 0; i<data_read; i++)
		{
			if (buffer[i] == '\n')
			{
				read_line.append(buffer + start_pos, i - start_pos + 1);
				start_pos = i + 1;
				queue_line(read_line);
				read_line.clear();
			}
		}
		read_line.append(buffer + start_pos, data_read - start_pos);
	}
}

bool DCCChatConnection::write_connection_data(IRCRawString &write_line, IRCRawString::size_type &write_pos, uicore::TCPConnection &connection)
{
	while (true)
	{
		if (write_line.length() != write_pos)
		{
			int bytes_written = connection.write(write_line.data() + write_pos, (int)(write_line.length() - write_pos));
			if (bytes_written == -1)
				return true;
			write_pos += bytes_written;
		}
		else
		{
			write_line.clear();
			write_pos = 0;
			if (!send_queue.empty())
			{
				if (send_queue.front().type == Message::type_disconnect)
				{
					send_queue.erase(send_queue.begin());
					return false;
				}
				else
				{
					write_line = send_queue.front().text + "\r\n";
					send_queue.erase(send_queue.begin());
				}
			}
		}
	}
}

void DCCChatConnection::queue_system(const IRCRawString &text)
{
	receive_queue.push_back(Message(Message::type_system, text));
	uicore::RunLoop::main_thread_async(uicore::bind_member(this, &DCCChatConnection::process));
}

void DCCChatConnection::queue_disconnected(const IRCRawString &reason)
{
	receive_queue.push_back(Message(Message::type_disconnect, reason));
	uicore::RunLoop::main_thread_async(uicore::bind_member(this, &DCCChatConnection::process));
}

void DCCChatConnection::queue_line(const IRCRawString &line)
{
	receive_queue.push_back(Message(Message::type_text, line));
	uicore::RunLoop::main_thread_async(uicore::bind_member(this, &DCCChatConnection::process));
}
