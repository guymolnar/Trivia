#pragma once
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);
};