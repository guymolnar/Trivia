#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : RoomRequestHandler(handlerFactory, user, roomId)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    return requestInfo.id == CLOSE_ROOM_REQUEST_CODE ||
        requestInfo.id == START_GAME_REQUEST_CODE || requestInfo.id == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.id == CLOSE_ROOM_REQUEST_CODE)
    {
        return closeRoom(requestInfo);
    }
    if (requestInfo.id == START_GAME_REQUEST_CODE)
    {
        return startGame(requestInfo);
    }
    if (requestInfo.id == GET_ROOM_STATE_REQUEST_CODE)
    {
        return getRoomState(requestInfo);
    }

    ErrorResponse err{ "Request not relevant to RoomAdminRequestHandler" };
    return { JsonResponsePacketSerializer::serializeResponse(err), this };
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo)
{
    try
    {
        Room* room = m_roomManager.getRoom(m_roomId);
        if (!room) 
        {
            throw std::exception("Room not found");
        }

        std::vector<std::string> members = room->getAllUsers();
        members.erase(std::remove(members.begin(), members.end(), m_user.getUsername()), members.end());
        LeaveRoomResponse leaveResponse{ 1 };
        m_roomManager.deleteRoom(m_roomId);
        CloseRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), m_handlerFactory.createMenuRequestHandler(m_user) };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo)
{
    try
    {
        Room* room = m_roomManager.getRoom(m_roomId);
        if (!room)
        {
            throw std::exception("Room not found");
        }
        std::vector<std::string> members = room->getAllUsers();
        members.erase(std::remove(members.begin(), members.end(), m_user.getUsername()), members.end());
        StartGameResponse startResponse{ 1 };

        room->setStatus(RoomStatus::ACTIVE);
        StartGameResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}