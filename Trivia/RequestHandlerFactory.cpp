#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* IDB, LoginManager loginManager) : m_database(IDB), m_loginManager(loginManager)
{

}
