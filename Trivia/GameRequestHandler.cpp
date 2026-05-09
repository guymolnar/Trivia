#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game, GameManager& gameManager) : m_handlerFactory(handlerFactory),
m_user(user), m_game(game), m_gameManager(gameManager)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    return requestInfo.id == LEAVE_GAME_REQUEST_CODE ||
        requestInfo.id == GET_QUESTION_REQUEST_CODE ||
        requestInfo.id == SUBMIT_ANSWER_REQUEST_CODE ||
        requestInfo.id == GET_GAME_RESULTS_REQUEST_CODE;
}

LoggedUser* GameRequestHandler::getLoggedUser()
{
    return &m_user;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.id == LEAVE_GAME_REQUEST_CODE)
    {
        return leaveGame(requestInfo);
    }
    if (requestInfo.id == GET_QUESTION_REQUEST_CODE)
    {
        return getQuestion(requestInfo);
    }
    if (requestInfo.id == SUBMIT_ANSWER_REQUEST_CODE)
    {
        return submitAnswer(requestInfo);
    }
    if (requestInfo.id == GET_GAME_RESULTS_REQUEST_CODE)
    {
        return getGameResults(requestInfo);
    }

    ErrorResponse err{ "Request not relevant to GameRequestHandler" };
    return { JsonResponsePacketSerializer::serializeResponse(err), this };
}