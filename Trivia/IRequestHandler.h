#pragma once
#include <vector>
#include "LoggedUser.h"

#define ERROR_RESPONSE_CODE 100
#define LOGIN_RESPONSE_CODE 101
#define SIGNUP_RESPONSE_CODE 102
#define LOGOUT_RESPONSE_CODE 103
#define GET_ROOMS_RESPONSE_CODE 104
#define GET_PLAYERS_IN_ROOM_RESPONSE_CODE 105
#define JOIN_ROOM_RESPONSE_CODE 106
#define CREATE_ROOM_RESPONSE_CODE 107
#define GET_HIGHSCORE_RESPONSE_CODE 108
#define GET_PERSONAL_STATS_RESPONSE_CODE 109
#define CLOSE_ROOM_RESPONSE_CODE 110
#define START_GAME_RESPONSE_CODE 111
#define GET_ROOM_STATE_RESPONSE_CODE 112
#define LEAVE_ROOM_RESPONSE_CODE 113


#define ERROR_REQUEST_CODE  200
#define LOGIN_REQUEST_CODE  201
#define SIGNUP_REQUEST_CODE 202
#define GET_PLAYERS_REQUEST_CODE 203
#define JOIN_ROOM_REQUEST_CODE 204
#define CREATE_ROOM_REQUEST_CODE 205
#define HIGH_SCORE_REQUEST_CODE 206
#define LOGOUT_REQUEST_CODE 207
#define GET_ROOMS_REQUEST_CODE 208
#define PERSONAL_STATS_REQUEST_CODE 209
#define CLOSE_ROOM_REQUEST_CODE 210
#define START_GAME_REQUEST_CODE 211
#define GET_ROOM_STATE_REQUEST_CODE 212
#define LEAVE_ROOM_REQUEST_CODE 213

class IRequestHandler;
struct RequestInfo {
	uint8_t id;
	time_t receivalTime;
	std::vector<uint8_t> buffer;
};

struct RequestResult {
	std::vector<uint8_t> buffer;
	IRequestHandler* newHandler = nullptr;
};

class IRequestHandler {
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
	virtual LoggedUser* getLoggedUser() { return nullptr; }
};