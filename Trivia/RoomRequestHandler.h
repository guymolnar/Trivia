#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include "Communicator.h"

class RequestHandlerFactory;

class RoomRequestHandler : public IRequestHandler
{
public:
    RoomRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId);
    LoggedUser* getLoggedUser() override;
    RequestResult getRoomState(const RequestInfo& requestInfo);

protected:
    LoggedUser m_user;
    unsigned int m_roomId;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};