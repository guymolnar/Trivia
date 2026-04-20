#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) : m_handlerFactory(factory) 
{

}


bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (requestInfo.id == LOGIN_REQUEST_CODE);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	LoginResponse loginResponse;
	loginResponse.status = requestInfo.id;

	RequestResult requestResult;
	requestResult.buffer = JsonResponsePacketSerializer::serializeResponse(loginResponse);
	requestResult.newHandler = new LoginRequestHandler();
	return requestResult;
}