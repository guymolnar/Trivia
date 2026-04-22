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


class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<uint8_t> buffer);

};