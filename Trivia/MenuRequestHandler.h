#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user);
	~MenuRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult signout(const RequestInfo& requestInfo);
	RequestResult getRooms(const RequestInfo& requestInfo);
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo); 
	RequestResult getPersonalStats(const RequestInfo& requestInfo);
	RequestResult getHighScore(const RequestInfo& requestInfo);
	RequestResult joinRoom(const RequestInfo& requestInfo);
	RequestResult createRoom(const RequestInfo& requestInfo);
};