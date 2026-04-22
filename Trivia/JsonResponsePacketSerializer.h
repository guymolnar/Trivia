#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <winsock2.h>
#include "IRequestHandler.h"
#include "Room.h"

using json = nlohmann::json;
struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct ErrorResponse {
	std::string message;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct GetHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};

class JsonResponsePacketSerializer {
public:
	static std::vector<uint8_t> serializeResponse(const LoginResponse& response);
	static std::vector<uint8_t> serializeResponse(const SignupResponse& response);
	static std::vector<uint8_t> serializeResponse(const ErrorResponse& response);
private:

};