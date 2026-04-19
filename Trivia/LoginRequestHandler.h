#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler() = default;
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);
};