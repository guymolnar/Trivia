#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());

	return LoginRequest{ j.at("username"), j.at("password") };
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

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer.begin(), buffer.end());
	return CreateRoomRequest{ j.at("roomName"), j.at("maxUsers"), j.at("questionsCount"), j.at("answersTimeout") };
}
