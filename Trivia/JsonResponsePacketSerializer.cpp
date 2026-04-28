#include "JsonResponsePacketSerializer.h"

std::vector<uint8_t> JsonResponsePacketSerializer::buildPacket(const std::string& jsonStr, uint8_t code)
{
	std::vector<uint8_t> packet;
	packet.push_back(code);
	uint32_t len = htonl(jsonStr.size());
	uint8_t* lenBytes = reinterpret_cast<uint8_t*>(&len);
	packet.insert(packet.end(), lenBytes, lenBytes + 4);
	packet.insert(packet.end(), jsonStr.begin(), jsonStr.end());
	return packet;
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
	json j = { {"status", response.status} };
	return buildPacket(j.dump(), LOGIN_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
	json j = { {"status", response.status} };
	return buildPacket(j.dump(), SIGNUP_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
	json j = { {"message", response.message} };
	return buildPacket(j.dump(), ERROR_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
	json j = { {"status", response.status} };
	return buildPacket(j.dump(), LOGOUT_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	std::string rooms = "";
	for (auto& room : response.rooms)
	{
		rooms += room.name + ", ";
	}
	if (!rooms.empty())
	{
		rooms.pop_back();
	}
	json j = { {"status", response.status}, {"Rooms", rooms} };
	return buildPacket(j.dump(), GET_ROOMS_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
	std::string players = "";
	for (auto& player : response.players)
	{
		players += player + ", ";
	}
	if (!players.empty())
	{
		players.pop_back();
	}
	json j = { {"PlayersInRoom", players} };
	return buildPacket(j.dump(), GET_PLAYERS_IN_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	json j = { {"status", response.status} };
	return buildPacket(j.dump(), JOIN_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	json j = { {"status", response.status} };
	return buildPacket(j.dump(), CREATE_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
	json j = { {"status", response.status}, {"HighScores", response.statistics} };
	return buildPacket(j.dump(), GET_HIGHSCORE_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
	json j = { {"status", response.status}, {"UserStatistics", response.statistics} };
	return buildPacket(j.dump(), GET_PERSONAL_STATS_RESPONSE_CODE);
}