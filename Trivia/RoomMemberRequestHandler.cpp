#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : RoomRequestHandler(handlerFactory, user, roomId)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return requestInfo.id == LEAVE_ROOM_REQUEST_CODE || requestInfo.id == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.id == LEAVE_ROOM_REQUEST_CODE)
    {
        return leaveRoom(requestInfo);
    }
    if (requestInfo.id == GET_ROOM_STATE_REQUEST_CODE)
    {
        return getRoomState(requestInfo);
    }

    ErrorResponse err{ "Request not relevant to RoomMemberRequestHandler" };
    return { JsonResponsePacketSerializer::serializeResponse(err), this };
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& requestInfo)
{
    try
    {
        Room* room = m_roomManager.getRoom(m_roomId);
        if (!room)
        {
            throw std::exception("Room not found");
        }
        room->removeUser(m_user);
        if (room->getAllUsers().empty())
        {
            m_roomManager.deleteRoom(m_roomId);
        }
        LeaveRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), m_handlerFactory.createMenuRequestHandler(m_user)};
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}
