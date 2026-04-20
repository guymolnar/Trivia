#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
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