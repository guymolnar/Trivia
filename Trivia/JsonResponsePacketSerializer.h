#pragma once
#include <string>
#include <vector>
#include "json.hpp"
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
class JsonResponsePacketSerializer {
public:
	static std::vector<uint8_t> serializeResponse(LoginResponse);
	static std::vector<uint8_t> serializeResponse(SignupResponse);
	static std::vector<uint8_t> serializeResponse(ErrorResponse);
private:

};