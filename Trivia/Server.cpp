#include "Server.h"

Server::Server() : m_communicator()
{

}

Server::~Server()
{

}

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, &m_communicator);
	t_connector.detach();

	getConsoleInput();
}

void Server::getConsoleInput()
{
    std::string input;
    while (true)
    {
        std::cin >> input;
        if (input == "EXIT")
        {
            break;
        }
    }
}