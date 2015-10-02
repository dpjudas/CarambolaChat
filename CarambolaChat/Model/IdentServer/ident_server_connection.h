
#pragma once

class IdentServer;

class IdentServerConnection
{
public:
	IdentServerConnection(IdentServer *server, uicore::TCPConnectionPtr connection);
	~IdentServerConnection();

private:
	void worker_main();
	bool received_message(std::string message);

	IdentServer *server;
	uicore::TCPConnectionPtr connection;
	uicore::NetworkConditionVariable change_event;
	std::mutex mutex;
	bool stop_flag = false;
	std::thread thread;
};
