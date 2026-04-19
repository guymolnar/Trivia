#include "Communicator.h"

static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

Communicator::Communicator()
{
	this->m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
	bindAndListen();
}

Communicator::~Communicator()
{
	try
	{
		::closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}
	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
}

void Communicator::startHandleRequests()
{
	while (true)
	{
		SOCKET clientSocket = ::accept(m_serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__ " - accept");
		}
		std::thread t(&Communicator::handleNewClient, this, clientSocket);
		t.detach();
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	{
		std::lock_guard<std::mutex> lock(m_clientsMutex);
		m_clients[clientSocket] = new LoginRequestHandler();
	}

	//std::string msg = "hello";
	//send(clientSocket, msg.c_str(), msg.size(), 0);

	uint8_t code = 0;
	while (recv(clientSocket, reinterpret_cast<char*>(&code), 1, 0) > 0)
	{
		uint8_t lenBytes[4] = {0};
		recv(clientSocket, reinterpret_cast<char*>(lenBytes), 4, 0);
		uint32_t jsonLen = ntohl(*reinterpret_cast<uint32_t*>(lenBytes));
		int totalReceived = 0;
		std::vector<uint8_t> payload(jsonLen);
		while (totalReceived < (int)jsonLen)
		{
			int bytes = recv(clientSocket, reinterpret_cast<char*>(payload.data()) + totalReceived, jsonLen - totalReceived, 0);
			if (bytes <= 0)
				break;
			totalReceived += bytes;
		}

		RequestInfo requestInfo;
		requestInfo.id = code;
		requestInfo.receivalTime = time(nullptr);
		requestInfo.buffer = payload;
		RequestResult result = m_clients[clientSocket]->handleRequest(requestInfo);
		send(clientSocket, reinterpret_cast<const char*>(result.buffer.data()), result.buffer.size(), 0);
		{
			std::lock_guard<std::mutex> lock(m_clientsMutex);
			delete m_clients[clientSocket];
			m_clients[clientSocket] = result.newHandler;
		}
	}

	{
		std::lock_guard<std::mutex> lock(m_clientsMutex);
		delete m_clients[clientSocket];
		m_clients.erase(clientSocket);
	}
	closesocket(clientSocket);
}