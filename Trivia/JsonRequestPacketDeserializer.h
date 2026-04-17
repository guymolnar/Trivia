#pragma once
#include <string>
#include <vector>

struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(std::vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<uint8_t> buffer);

};