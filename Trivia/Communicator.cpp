#include "Communicator.h"

static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
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
		m_clients[clientSocket] = new LoginRequestHandler(m_handlerFactory);
	}

	RequestInfo requestInfo;
	while (readMessage(clientSocket, requestInfo))
	{
		IRequestHandler* handler = m_clients[clientSocket];

		if (!handler->isRequestRelevant(requestInfo))
		{
			continue;
		}
		RequestResult result = handler->handleRequest(requestInfo);

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

bool Communicator::recvAll(SOCKET s, char* buffer, int length)
{
	int total = 0;
	while (total < length)
	{
		int bytes = recv(s, buffer + total, length - total, 0);
		if (bytes <= 0)
			return false;
		total += bytes;
	}
	return true;
}

bool Communicator::readMessage(SOCKET clientSocket, RequestInfo& requestInfo)
{
	uint8_t code;
	if (!recvAll(clientSocket, reinterpret_cast<char*>(&code), 1))
	{
		return false;
	}
	uint8_t lenBytes[4];
	if (!recvAll(clientSocket, reinterpret_cast<char*>(lenBytes), 4))
	{
		return false;
	}

	uint32_t jsonLen;
	memcpy(&jsonLen, lenBytes, 4);
	jsonLen = ntohl(jsonLen);

	if (jsonLen > 4096)
	{
		return false;
	}

	std::vector<uint8_t> payload(jsonLen);
	if (!recvAll(clientSocket, reinterpret_cast<char*>(payload.data()), jsonLen))
	{
		return false;
	}

	requestInfo.id = code;
	requestInfo.receivalTime = time(nullptr);
	requestInfo.buffer = payload;
	return true;
}