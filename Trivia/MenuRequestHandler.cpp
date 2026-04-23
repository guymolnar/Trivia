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