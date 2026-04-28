#pragma once
#include "RoomRequestHandler.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public RoomRequestHandler
{
public:
    RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, unsigned int roomId);
    ~RoomMemberRequestHandler() = default;
    bool isRequestRelevant(const RequestInfo& requestInfo) override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
    RequestResult leaveRoom(const RequestInfo& requestInfo);
};