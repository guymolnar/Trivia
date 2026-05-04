#pragma once
#pragma once
#include <string>

struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string mail;
	std::string address;
	std::string phone;
	std::string birthday;
};

struct GetPlayersInRoomRequest {
	unsigned int roomId;
};

struct JoinRoomRequest {
	unsigned int roomId;
};

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionsCount;
	unsigned int answersTimeout;
};

struct CloseRoomRequest {
	unsigned int roomId;
};

struct StartGameRequest {
	unsigned int roomId;
};

struct GetRoomStateRequest {
	unsigned int roomId;
};

struct LeaveRoomRequest {
	unsigned int roomId;
};