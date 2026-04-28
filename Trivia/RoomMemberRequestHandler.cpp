#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_user(user),
    m_roomId(roomId),
    m_roomManager(handlerFactory.getRoomManager()),
    m_handlerFactory(handlerFactory)
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

LoggedUser* RoomMemberRequestHandler::getLoggedUser()
{
    return &m_user;
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& requestInfo)
{
    try
    {
        LeaveRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}