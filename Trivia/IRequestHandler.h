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
	bool isRequestRelevant(const RequestInfo& requestInfo);
	RequestResult handleRequest(const RequestInfo& requestInfo);
};