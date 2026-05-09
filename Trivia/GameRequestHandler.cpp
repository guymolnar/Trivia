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