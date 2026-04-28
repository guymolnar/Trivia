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