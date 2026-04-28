#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* IDB) : m_database(IDB)
{

}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(*this, user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, unsigned int roomId)
{
    return new RoomAdminRequestHandler(*this, user, roomId);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, unsigned int roomId)
{
    return new RoomMemberRequestHandler(*this, user, roomId);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return LoginManager::getInstance(m_database);
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return RoomManager::getInstance();
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return StatisticsManager::getInstance();
}