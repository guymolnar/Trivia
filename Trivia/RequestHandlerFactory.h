#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory {
public:
	static RequestHandlerFactory& getInstance(IDatabase* IDB)
	{
		static RequestHandlerFactory instance(IDB);
		return instance;
	}
	RequestHandlerFactory(const RequestHandlerFactory&) = delete;
	void operator=(const RequestHandlerFactory&) = delete;
	~RequestHandlerFactory() = default;
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
private:
	RequestHandlerFactory(IDatabase* IDB);
	IDatabase* m_database;
};