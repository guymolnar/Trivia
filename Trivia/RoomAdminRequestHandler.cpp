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
        m_handlerFactory.getRoomManager().deleteRoom(m_room.getRoomMetadata().id);
        CloseRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}