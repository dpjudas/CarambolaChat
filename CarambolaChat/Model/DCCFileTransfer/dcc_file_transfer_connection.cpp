
#include "precomp.h"
#include "dcc_file_transfer_connection.h"

#ifndef WIN32
#include <arpa/inet.h>
#endif

DCCFileTransferConnection::DCCFileTransferConnection(const uicore::SocketName &socket_name)
: socket_name(socket_name), bytes_received(0), status(status_not_started)
{
}

DCCFileTransferConnection::~DCCFileTransferConnection()
{
	abort();
}

void DCCFileTransferConnection::start(const std::string &output_filename)
{
	std::unique_lock<std::mutex> lock(mutex);
	if (status != status_not_started)
		throw uicore::Exception("DCC file transfer can only be started once");

	status = status_connecting;
	status_text = "Connecting..";
	filename = output_filename;
	lock.unlock();
	change_event.notify();
	thread = std::thread(&DCCFileTransferConnection::worker_main, this);
}

DCCFileTransferConnection::Status DCCFileTransferConnection::get_status()
{
	std::unique_lock<std::mutex> lock(mutex);
	return status;
}

std::string DCCFileTransferConnection::get_status_text()
{
	std::unique_lock<std::mutex> lock(mutex);
	return status_text;
}

unsigned int DCCFileTransferConnection::get_bytes_received()
{
	std::unique_lock<std::mutex> lock(mutex);
	return bytes_received;
}

void DCCFileTransferConnection::abort()
{
	std::unique_lock<std::mutex> lock(mutex);
	if (abort_flag)
		return;
	abort_flag = true;
	lock.unlock();
	change_event.notify();
	thread.join();
}

void DCCFileTransferConnection::worker_main()
{
	try
	{
		connection = uicore::TCPConnection::connect(socket_name);

		std::unique_lock<std::mutex> lock(mutex);

		//connection.set_big_endian_mode();
		status = status_receiving;
		status_text = "Downloading..";

		auto outputfile = uicore::File::create_always(filename);
		auto buffer = uicore::DataBuffer::create(1024 * 1024);
		int total_received_counter = 0;
		while (true)
		{
			if (abort_flag)
			{
				status = status_aborted;
				status_text = "Abort requested by user";
				connection = uicore::TCPConnectionPtr();
				return;
			}

			//int wakeup_reason = uicore::Event::wait(abort_event, connection.get_read_event(), 60*1000);
			int received = connection->read(buffer->data(), (int)buffer->size());
			if (received == 0)
			{
				status = status_finished_transfer;
				status_text = "Transfer complete";
				connection = uicore::TCPConnectionPtr();
				return;
			}
			else if (received == -1)
			{
				uicore::NetworkEvent *events[] = { connection.get() };
				if (!change_event.wait(lock, 1, events))
				{
					status = status_error;
					status_text = "Received no data for 60 seconds and gave up";
					return;
				}
				continue;
			}

			outputfile->write(buffer->data(), received);
			total_received_counter += received;
			bytes_received += received;

			int network_total_received_counter = htonl(total_received_counter);

			int write_pos = 0;
			char *write_data = (char*)&network_total_received_counter;
			int write_len = sizeof(int);
			while (write_pos != write_len)
			{
				if (abort_flag)
				{
					status = status_aborted;
					status_text = "Abort requested by user";
					connection = uicore::TCPConnectionPtr();
					return;
				}

				int written = connection->write(write_data + write_pos, write_len - write_pos);
				if (written != -1)
				{
					write_pos += written;
				}
				else
				{
					uicore::NetworkEvent *events[] = { connection.get() };
					if (!change_event.wait(lock, 1, events))
					{
						status = status_error;
						status_text = "Received no data for 60 seconds and gave up";
						return;
					}
				}
			}
		}
	}
	catch (uicore::Exception &e)
	{
		connection = uicore::TCPConnectionPtr();
		std::unique_lock<std::mutex> lock(mutex);
		status = status_error;
		status_text = e.message;
	}
}
