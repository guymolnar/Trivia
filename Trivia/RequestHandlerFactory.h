#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory {
public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};