#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_handlerFactory(handlerFactory),
    m_user(user),
    m_roomManager(handlerFactory.getRoomManager()),
    m_room(*handlerFactory.getRoomManager().getRoom(roomId))
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return requestInfo.id == CLOSE_ROOM_REQUEST_CODE ||
        requestInfo.id == START_GAME_REQUEST_CODE || requestInfo.id == GET_ROOM_STATE_REQUEST_CODE;
}