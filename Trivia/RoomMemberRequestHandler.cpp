#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_user(user),
    m_roomId(roomId),
    m_roomManager(handlerFactory.getRoomManager()),
    m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return requestInfo.id == LEAVE_ROOM_REQUEST_CODE || requestInfo.id == GET_ROOM_STATE_REQUEST_CODE;
}