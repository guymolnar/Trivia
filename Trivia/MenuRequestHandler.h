#pragma once
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};