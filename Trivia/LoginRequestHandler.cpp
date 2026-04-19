#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (requestInfo.id == LOGIN_REQUEST_CODE);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;
	requestResult.newHandler = new LoginRequestHandler();
	return requestResult;
}