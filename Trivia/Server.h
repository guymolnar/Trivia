#pragma once

#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Communicator.h"
#include <WinSock2.h>
#include "IDatabase.h"


class Server
{
public:
	Server();
	~Server();
	void run();
	
private:
	Communicator m_communicator;
	IDatabase* m_database;
	void getConsoleInput();
};