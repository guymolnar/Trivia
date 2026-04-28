#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"

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
    RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, unsigned int roomId);
    LoginManager& getLoginManager();
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();
private:
    RequestHandlerFactory(IDatabase* IDB);
    IDatabase* m_database;
};