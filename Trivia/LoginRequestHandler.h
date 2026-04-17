#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
};