#include "RoomRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomRequestHandler::RoomRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId)
    : m_user(user),
    m_roomId(roomId),
    m_roomManager(handlerFactory.getRoomManager()),
    m_handlerFactory(handlerFactory)
{
}

LoggedUser* RoomRequestHandler::getLoggedUser()
{
    return &m_user;
}

RequestResult RoomRequestHandler::getRoomState(const RequestInfo& requestInfo)
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