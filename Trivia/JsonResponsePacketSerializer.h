#pragma once
#include <string>
#include <vector>

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
	std::vector<uint8_t> serializeResponse(LoginResponse);
	std::vector<uint8_t> serializeResponse(SignupResponse);
	std::vector<uint8_t> serializeResponse(ErrorResponse);
private:

};