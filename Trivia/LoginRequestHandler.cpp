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
		if (!isPasswordValid(req.password))
		{
			throw std::exception("Invalid password");
		}
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

bool LoginRequestHandler::isPasswordValid(const std::string& password)
{
	if (password.length() < 8)
	{
		return false;
	}

	std::regex hasUpper("[A-Z]");
	std::regex hasLower("[a-z]");
	std::regex hasDigit("[0-9]");
	
	return std::regex_search(password, hasUpper) &&
		std::regex_search(password, hasLower) &&
		std::regex_search(password, hasDigit);
}