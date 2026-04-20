#pragma once
#include <deque>
#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <WinSock2.h>
#include <unordered_map>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

class Communicator {
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequests();
private:
	SOCKET m_serverSocket;
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	std::mutex m_clientsMutex;
	RequestHandlerFactory& m_handlerFactory;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	bool readMessage(SOCKET clientSocket, RequestInfo& requestInfo);
	static bool recvAll(SOCKET s, char* buffer, int length);
};