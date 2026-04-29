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
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), LOGIN_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), SIGNUP_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
	json responseJson = { {"message", response.message} };
	return buildPacket(responseJson.dump(), ERROR_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), LOGOUT_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	std::string rooms = "";
	for (auto& room : response.rooms)
	{
		rooms += std::to_string(room.id) + ":" + room.name + ", ";
	}
	if (!rooms.empty())
	{
		rooms.pop_back();
		rooms.pop_back();
	}
	json responseJson = { {"status", response.status}, {"Rooms", rooms} };
	return buildPacket(responseJson.dump(), GET_ROOMS_RESPONSE_CODE);
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
		players.pop_back();
	}
	json responseJson = { {"PlayersInRoom", players} };
	return buildPacket(responseJson.dump(), GET_PLAYERS_IN_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), JOIN_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	json responseJson = { {"status", response.status}, {"roomId", response.roomId} };
	return buildPacket(responseJson.dump(), CREATE_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
	json responseJson = { {"status", response.status}, {"HighScores", response.statistics} };
	return buildPacket(responseJson.dump(), GET_HIGHSCORE_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
	json responseJson = { {"status", response.status}, {"UserStatistics", response.statistics} };
	return buildPacket(responseJson.dump(), GET_PERSONAL_STATS_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), CLOSE_ROOM_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), START_GAME_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
	json responseJson = { {"status", response.status}, {"hasGameBegan", response.hasGameBegun}, {"players", response.players}, {"questionCount", response.questionCount}, {"answerTimeOut", response.answerTimeout} };
	return buildPacket(responseJson.dump(), GET_ROOM_STATE_RESPONSE_CODE);
}

std::vector<uint8_t> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
	json responseJson = { {"status", response.status} };
	return buildPacket(responseJson.dump(), LEAVE_ROOM_RESPONSE_CODE);
}