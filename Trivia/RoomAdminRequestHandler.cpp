#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_handlerFactory(handlerFactory),
    m_user(user),
    m_roomManager(handlerFactory.getRoomManager()),
    m_room(*handlerFactory.getRoomManager().getRoom(roomId))
{
}

