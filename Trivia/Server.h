#pragma once

#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Communicator.h"
#include <WinSock2.h>
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "RequestHandlerFactory.h"


class Server
{
public:
    static Server& getInstance()
    {
        static Server instance;
        return instance;
    }
    Server(const Server&) = delete;
    void operator=(const Server&) = delete;
	void run();

	
private:
    Server();
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
	void getConsoleInput();
};