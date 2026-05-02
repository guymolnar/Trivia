#pragma once

#include "RoomRequestHandler.h"
class RequestHandlerFactory;

class RoomAdminRequestHandler : public RoomRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId);
	~RoomAdminRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
	
private:
	RequestResult closeRoom(const RequestInfo& requestInfo);
	RequestResult startGame(const RequestInfo& requestInfo);
};

