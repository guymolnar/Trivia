#include "Server.h"

Server::Server() : m_database(&SqliteDataBase::getInstance())
{
    m_database->open();
}


void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, &Communicator::getInstance(RequestHandlerFactory::getInstance(m_database)));
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