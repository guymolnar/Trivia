#pragma once
#include <vector>

#define LOGIN_REQUEST_CODE 1
#define SIGNUP_REQUEST_CODE 2
#define ERROR_REQUEST_CODE 0
class IRequestHandler;
struct RequestInfo {
	uint8_t id;
	time_t receivalTime;
	std::vector<uint8_t> buffer;
};

struct RequestResult {
	std::vector<uint8_t> buffer;
	IRequestHandler* newHandler = nullptr;
};

class IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};