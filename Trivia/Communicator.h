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

#define CODE_SIZE 1
#define LENGTH_SIZE 4
#define MAX_MESSAGE_SIZE 4096

class Communicator {
public:
	static Communicator& getInstance(RequestHandlerFactory& handlerFactory)
	{
		static Communicator instance(handlerFactory);
		return instance;
	}

	Communicator(const Communicator&) = delete;
	void operator=(const Communicator&) = delete;
	~Communicator();
	void startHandleRequests();
	void broadcast(const std::vector<std::string>& usernames, const std::vector<uint8_t>& message);
private:
	Communicator(RequestHandlerFactory& handlerFactory);
	SOCKET m_serverSocket;
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	std::mutex m_clientsMutex;
	RequestHandlerFactory& m_handlerFactory;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	bool readMessage(SOCKET clientSocket, RequestInfo& requestInfo);
	static bool recvAll(SOCKET s, char* buffer, int length);
};