#pragma once
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include <unordered_map>
#include "IRequestHandler.h"

class Communicator {
public:
	Communicator();
	~Communicator();
	void startHandleRequests();
private:
	SOCKET m_serverSocket;
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
};