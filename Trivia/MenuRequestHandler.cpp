#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user): m_handlerFactory(handlerFactory), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    return RequestResult{};
}