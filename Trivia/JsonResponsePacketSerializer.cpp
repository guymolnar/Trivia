#include "JsonResponsePacketSerializer.h"

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
	json j = { {"status", response.status} };
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(LOGIN_RESPONSE_CODE);

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t * lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());
	
	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
	json j = { {"status", response.status} };
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(SIGNUP_RESPONSE_CODE);

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());

	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
	json j = { {"message", response.message}};
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(ERROR_RESPONSE_CODE);

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());

	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
	json j = { {"status", response.status} };
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(LOGOUT_RESPONSE_CODE);

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());

	return packet;
}

