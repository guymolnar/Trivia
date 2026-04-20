#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) : m_handlerFactory(factory) 
{

}


bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (requestInfo.id == LOGIN_REQUEST_CODE || requestInfo.id == SIGNUP_REQUEST_CODE);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	if (requestInfo.id == LOGIN_REQUEST_CODE)
	{
		return login(requestInfo);
	}
		
	return signup(requestInfo);
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
	try
	{
		LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		m_handlerFactory.getLoginManager().login(req.username, req.password);

		LoginResponse response;
		response.status = 1;

		RequestResult result;
		result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createMenuRequestHandler();
		return result;
	}
	catch (const std::exception&)
	{
		LoginResponse response;
		response.status = 0;

		RequestResult result;
		result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
		return result;
	}
}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
	try
	{
		SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		m_handlerFactory.getLoginManager().signup(req.username, req.password, req.email);

		SignupResponse response;
		response.status = 1;

		RequestResult result;
		result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createMenuRequestHandler();
		return result;
	}
	catch (const std::exception&)
	{
		SignupResponse response;
		response.status = 0;

		RequestResult result;
		result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
		return result;
	}
}