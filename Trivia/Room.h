#pragma once
#include <string>

enum RoomStatus
{
	ACTIVE,
	INACTIVE
};

struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestions;
	unsigned int timePerQuestions;
	RoomStatus status;
};



class Room {

};