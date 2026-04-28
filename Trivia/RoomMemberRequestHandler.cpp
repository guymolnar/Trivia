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
        Room* room = m_roomManager.getRoom(m_roomId);
        if (!room)
        {
            throw std::exception("Room not found");
        }
        room->removeUser(m_user);
        LeaveRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& requestInfo)
{
    try
    {
        Room* room = m_roomManager.getRoom(m_roomId);
        if (!room)
        {
            throw std::exception("Room not found");
        }
        RoomData meta = room->getRoomMetadata();
        std::vector<std::string> players = room->getAllUsers();
        GetRoomStateResponse response{ 1, false, players, meta.numOfQuestions, meta.timePerQuestions };
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}