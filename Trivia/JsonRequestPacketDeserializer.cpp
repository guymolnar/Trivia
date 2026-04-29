#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json requestJson = json::parse(buffer.begin(), buffer.end());
	return LoginRequest{ requestJson.at("username"), requestJson.at("password") };
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	json requestJson = json::parse(buffer.begin(), buffer.end());
	return SignupRequest{ requestJson.at("username"), requestJson.at("password"), requestJson.at("mail"), requestJson.at("address"), requestJson.at("phone"), requestJson.at("birthday") };
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<uint8_t> buffer)
{
	json requestJson = json::parse(buffer.begin(), buffer.end());
	return GetPlayersInRoomRequest{ requestJson.at("roomId") };
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<uint8_t> buffer)
{
	json requestJson = json::parse(buffer.begin(), buffer.end());
	return JoinRoomRequest{ requestJson.at("roomId") };
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<uint8_t> buffer)
{
	json requestJson = json::parse(buffer.begin(), buffer.end());
	return CreateRoomRequest{ requestJson.at("roomName"), requestJson.at("maxUsers"), requestJson.at("questionsCount"), requestJson.at("answersTimeout") };
}