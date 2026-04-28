#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId);
	~RoomAdminRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
	LoggedUser* getLoggedUser() override;

	
private:
	LoggedUser m_user;
	unsigned int m_roomId;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult closeRoom(const RequestInfo& requestInfo);
	RequestResult startGame(const RequestInfo& requestInfo);
	RequestResult getRoomState(const RequestInfo& requestInfo);
};

