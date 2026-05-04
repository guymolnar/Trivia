#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "Room.h"
#include "Requests.h"
using json = nlohmann::json;


class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(const std::vector<uint8_t>& buffer);
	static SignupRequest deserializeSignupRequest(const std::vector<uint8_t>& buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const std::vector<uint8_t>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<uint8_t>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<uint8_t>& buffer);

};