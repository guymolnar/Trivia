#pragma once
#include <vector>

#define LOGIN_RESPONSE_CODE 101
#define SIGNUP_RESPONSE_CODE 102
#define ERROR_RESPONSE_CODE 100
#define LOGOUT_RESPONSE_CODE 103
#define GET_ROOMS_RESPONSE_CODE 104
#define GET_PLAYERS_IN_ROOM_RESPONSE_CODE 105
#define JOIN_ROOM_RESPONSE_CODE 106
#define CREATE_ROOM_RESPONSE_CODE 107
#define GET_HIGHSCORE_RESPONSE_CODE 108
#define GET_PERSONAL_STATS_RESPONSE_CODE 109

#define ERROR_REQUEST_CODE  200
#define LOGIN_REQUEST_CODE  201
#define SIGNUP_REQUEST_CODE 202
#define GET_PLAYERS_REQUEST_CODE 203
#define JOIN_ROOM_REQUEST_CODE 204
#define CREATE_ROOM_REQUEST_CODE 205
#define HIGH_SCORE_REQUEST_CODE 206
#define LOGOUT_REQUEST_CODE 207
#define GET_ROOMS_REQUEST_CODE 208

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
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};