#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "Room.h"
using json = nlohmann::json;

struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
	std::string address;
	std::string phone;
	std::string birthday;
};

struct GetPlayersInRoomRequest {
	unsigned int roomId;
};

struct JoinRoomRequest {
	unsigned int roomId;
};

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionsCount;
	unsigned int answersTimeout;
};

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(const std::vector<uint8_t>& buffer);
	static SignupRequest deserializeSignupRequest(const std::vector<uint8_t>& buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const std::vector<uint8_t>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<uint8_t>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<uint8_t>& buffer);

};