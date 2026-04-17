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