#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
class RequestHandlerFactory;

class RoomRequestHandler : public IRequestHandler
{
protected:
    LoggedUser m_user;
    unsigned int m_roomId;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
    RoomRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId);
    RequestResult getRoomState(const RequestInfo& requestInfo);
};