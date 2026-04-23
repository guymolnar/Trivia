#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user): m_handlerFactory(handlerFactory), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return requestInfo.id == LOGOUT_REQUEST_CODE ||
        requestInfo.id == GET_ROOMS_REQUEST_CODE ||
        requestInfo.id == GET_PLAYERS_REQUEST_CODE ||
        requestInfo.id == JOIN_ROOM_REQUEST_CODE ||
        requestInfo.id == CREATE_ROOM_REQUEST_CODE ||
        requestInfo.id == HIGH_SCORE_REQUEST_CODE ||
        requestInfo.id == PERSONAL_STATS_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.id == LOGOUT_REQUEST_CODE)
    {
        return signout(requestInfo);
    }
    if (requestInfo.id == GET_ROOMS_REQUEST_CODE)
    {
        return getRooms(requestInfo);
    }
    if (requestInfo.id == GET_PLAYERS_REQUEST_CODE)
    {
        return getPlayersInRoom(requestInfo);
    }
    if (requestInfo.id == PERSONAL_STATS_REQUEST_CODE)
    {
        return getPersonalStats(requestInfo);
    }
    if (requestInfo.id == HIGH_SCORE_REQUEST_CODE)
    {
        return getHighScore(requestInfo);
    }
    if (requestInfo.id == JOIN_ROOM_REQUEST_CODE)
    {
        return joinRoom(requestInfo);
    }
    if (requestInfo.id == CREATE_ROOM_REQUEST_CODE)
    {
        return createRoom(requestInfo);
    }

    ErrorResponse err{ "Request not relevant to MenuRequestHandler" };
    return { JsonResponsePacketSerializer::serializeResponse(err), this };
}

RequestResult MenuRequestHandler::signout(const RequestInfo& requestInfo)
{
    try 
    {
        m_handlerFactory.getLoginManager().logout(m_user.getUsername());
        LogoutResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
    }
    catch(const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo)
{
    try
    {
        
        std::vector<RoomData> rooms = m_handlerFactory.getRoomManager().getRooms();
        GetRoomsResponse response{1, rooms};
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{
    try
    {

        GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
        std::vector<std::string> roomUsers = m_handlerFactory.getRoomManager().getRoom(req.roomId)->getAllUsers();
        GetPlayersInRoomResponse response{roomUsers};
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo)
{
    try
    {
        std::vector<std::string> stats = m_handlerFactory.getStatisticsManager().getUserStatistics(m_user.getUsername());
        GetPersonalStatsResponse response{1, stats };
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo)
{
    try
    {
        std::vector<std::string> highScore = m_handlerFactory.getStatisticsManager().getHighScore();
        GetPersonalStatsResponse response{ 1, highScore };
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo)
{
    try
    {
        JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
        m_handlerFactory.getRoomManager().getRoom(req.roomId)->addUser(m_user);
        JoinRoomResponse response{ 1 };
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}