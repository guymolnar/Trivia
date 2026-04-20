#include "Server.h"

Server::Server() : m_database(&SqliteDataBase::getInstance()), m_handlerFactory(m_database)
{
    m_database->open();
}


void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, &Communicator::getInstance(m_handlerFactory));
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