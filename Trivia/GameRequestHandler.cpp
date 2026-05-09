#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game, GameManager& gameManager) : m_handlerFactory(handlerFactory),
m_user(user), m_game(game), m_gameManager(gameManager)
{
}

