#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "AESCryptoAlgorithm.h"
#include "SqliteDataBase.h"

static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	m_crypto = new AESCryptoAlgorithm(SqliteDataBase::getInstance().getOrCreateCryptoKey());
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
		for (auto& pair : m_clients)
		{
			delete pair.second;
		}
		m_clients.clear();
		::closesocket(this->m_serverSocket);
		delete m_crypto;
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
	try
	{
		{
			std::lock_guard<std::mutex> lock(m_clientsMutex);
			m_clients[clientSocket] = new LoginRequestHandler(m_handlerFactory);
		}

		RequestInfo requestInfo;
		while (readMessage(clientSocket, requestInfo))
		{
			IRequestHandler* handler;
			{
				std::lock_guard<std::mutex> lock(m_clientsMutex);
				handler = m_clients[clientSocket];
			}

			if (!handler->isRequestRelevant(requestInfo))
			{
				ErrorResponse err{ "Request not relevant" };
				auto response = JsonResponsePacketSerializer::serializeResponse(err);
				send(clientSocket, reinterpret_cast<const char*>(response.data()), response.size(), 0);
				continue;
			}

			RequestResult result = handler->handleRequest(requestInfo);
			send(clientSocket, reinterpret_cast<const char*>(result.buffer.data()), result.buffer.size(), 0);

			{
				std::lock_guard<std::mutex> lock(m_clientsMutex);
				IRequestHandler* old = m_clients[clientSocket];
				m_clients[clientSocket] = result.newHandler;
				if (old != result.newHandler)
					delete old;
			}

			if (!result.newHandler) break;
		}

		{
			std::lock_guard<std::mutex> lock(m_clientsMutex);
			IRequestHandler* handler = m_clients[clientSocket];
			if (handler)
			{
				LoggedUser* user = handler->getLoggedUser();
				if (user)
				{
					m_handlerFactory.getLoginManager().logout(user->getUsername());
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Client handler error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown error in client handler" << std::endl;
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
	if (!recvAll(clientSocket, reinterpret_cast<char*>(&code), CODE_SIZE))
	{
		return false;
	}
	uint8_t lenBytes[LENGTH_SIZE];
	if (!recvAll(clientSocket, reinterpret_cast<char*>(lenBytes), LENGTH_SIZE))
	{
		return false;
	}

	uint32_t jsonLen;
	memcpy(&jsonLen, lenBytes, LENGTH_SIZE);
	jsonLen = ntohl(jsonLen);

	if (jsonLen > MAX_MESSAGE_SIZE)
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
	requestInfo.buffer = m_crypto->decrypt(payload);
	return true;
}

void Communicator::sendResponse(SOCKET clientSocket, const std::vector<uint8_t>& serialized)
{
	uint8_t code = serialized[0];
	std::vector<uint8_t> body(serialized.begin() + 5, serialized.end());   //skipping [code][len]
	std::vector<uint8_t> cipher = m_crypto->encrypt(body);

	std::vector<uint8_t> packet;
	packet.push_back(code);
	uint32_t len = htonl(static_cast<uint32_t>(cipher.size()));
	const uint8_t* lenBytes = reinterpret_cast<const uint8_t*>(&len);
	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), cipher.begin(), cipher.end());

	send(clientSocket, reinterpret_cast<const char*>(packet.data()), static_cast<int>(packet.size()), 0);
}