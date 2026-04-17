#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <winsock2.h>
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
	static std::vector<uint8_t> serializeResponse(const LoginResponse& response);
	static std::vector<uint8_t> serializeResponse(const SignupResponse& response);
	static std::vector<uint8_t> serializeResponse(const ErrorResponse& response);
private:

};