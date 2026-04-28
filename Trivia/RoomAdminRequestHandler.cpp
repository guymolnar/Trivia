#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_user(user),
    m_roomId(roomId),
    m_roomManager(handlerFactory.getRoomManager()),
    m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
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

LoggedUser* RoomAdminRequestHandler::getLoggedUser()
{
    return &m_user;
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo)
{
    try
    {
        m_handlerFactory.getRoomManager().deleteRoom(m_roomId);
        CloseRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
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
        StartGameResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& requestInfo)
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