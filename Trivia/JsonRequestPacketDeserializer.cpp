#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());

	LoginRequest info = { j.at("username"), j.at("password") };
	return info;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());

	return SignupRequest{ j.at("username"), j.at("password"), j.at("mail"), j.at("address"), j.at("phone"), j.at("birthday") };
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());
	return GetPlayersInRoomRequest{ j.at("roomId") };
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());
	return JoinRoomRequest{ j.at("roomId") };
}