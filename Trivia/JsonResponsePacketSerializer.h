#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <winsock2.h>
#include "IRequestHandler.h"
#include "Room.h"
#include "Responses.h"

using json = nlohmann::json;

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
	static std::vector<uint8_t> serializeResponse(const CloseRoomResponse& response);
	static std::vector<uint8_t> serializeResponse(const StartGameResponse& response);
	static std::vector<uint8_t> serializeResponse(const GetRoomStateResponse& response);
	static std::vector<uint8_t> serializeResponse(const LeaveRoomResponse& response);
private:
	static std::vector<uint8_t> buildPacket(const std::string& jsonStr, uint8_t code);
};