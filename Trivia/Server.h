#pragma once

#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>


class Server
{
public:
	Server();
	~Server();
	void run();

private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(const SOCKET client_socket);
	void safeDeleteUser(const SOCKET id);
	SOCKET _socket;
};