#pragma once
#include <vector>

struct RequestInfo {
	uint8_t id;
	time_t receivalTime;
	std::vector<uint8_t> buffer;
};

struct RequestResult {
	std::vector<uint8_t> buffer;
	IRequestHandler* newHandler;
};

class IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};