#include "JsonResponsePacketSerializer.h"

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
	json j = { {"status", 1} };
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(1); // loginResponse code

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t * lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());
	
	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
	json j = { {"status", 1} };
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(2); // loginResponse code

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());

	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{
	json j = { {"message", "ERROR"}};
	std::string jsonStr = j.dump();

	std::vector<uint8_t> packet;
	packet.push_back(3); // loginResponse code

	uint32_t len = htonl(jsonStr.size()); //converting endianess to be the same as the network standard
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);

	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());

	return packet;
}

