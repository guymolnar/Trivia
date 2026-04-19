#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (requestInfo.id == LOGIN_REQUEST_CODE);
}