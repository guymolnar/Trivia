#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	std::string jsonStr = std::string(buffer.begin(), buffer.end());
	json j = json::parse(jsonStr);

	std::string username = j.at("username");
	std::string password = j.at("password");

	LoginRequest info = { username, password };
	return info;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	std::string jsonStr = std::string(buffer.begin(), buffer.end());
	json j = json::parse(jsonStr);

	std::string username = j.at("username");
	std::string password = j.at("password");
	std::string mail = j.at("mail");

	SignupRequest info = { username, password, mail };
	return info;
}