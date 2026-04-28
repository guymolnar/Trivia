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
	unsigned int roomId;
};

struct CloseRoomResponse {
	unsigned int status;
};

struct StartGameResponse {
	unsigned int status;
};

struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

class JsonResponsePacketSerializer {
public:
	static std::vector<uint8_t> serializeResponse(const LoginResponse& response);
	static std::vector<uint8_t> serializeResponse(const SignupResponse& response);
	static std::vector<uint8_t> serializeResponse(const ErrorResponse& response);
	static std::vector<uint8_t> serializeResponse(const LogoutResponse& response);
	static std::vector<uint8_t> serializeResponse(const GetRoomsResponse& response);
	static std::vector<uint8_t> serializeResponse(const GetPlayersInRoomResponse& response);
	static std::vector<uint8_t> serializeResponse(const JoinRoomResponse& response);
	static std::vector<uint8_t> serializeResponse(const CreateRoomResponse& response);
	static std::vector<uint8_t> serializeResponse(const GetHighScoreResponse& response);
	static std::vector<uint8_t> serializeResponse(const GetPersonalStatsResponse& response);
private:
	static std::vector<uint8_t> buildPacket(const std::string& jsonStr, uint8_t code);
};