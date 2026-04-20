#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory {
public:
	RequestHandlerFactory(IDatabase* IDB, LoginManager loginManager);
	~RequestHandlerFactory() = default;
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};