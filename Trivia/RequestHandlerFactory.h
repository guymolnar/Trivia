#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

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
    MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
    LoginManager& getLoginManager();
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();
private:
    RequestHandlerFactory(IDatabase* IDB);
    IDatabase* m_database;
};