#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"

class RequestHandlerFactory;
class GameRequestHandler : public IRequestHandler {
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game, GameManager& gameManager);
	~GameRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
	LoggedUser* getLoggedUser() override;
private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(const RequestInfo& requestInfo) const;
	RequestResult submitAnswer(const RequestInfo& requestInfo);
	RequestResult getGameResults(const RequestInfo& requestInfo);
	RequestResult leaveGame(const RequestInfo& requestInfo);
};