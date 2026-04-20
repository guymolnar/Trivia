#pragma once
#include <string>
#include <vector>
#include "json.hpp"
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

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<uint8_t> buffer);

};