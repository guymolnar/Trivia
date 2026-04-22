#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	LoggedUser m_user;
};