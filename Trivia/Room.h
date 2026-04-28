#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>

enum RoomStatus
{
	INACTIVE,
	ACTIVE
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
public:
	Room(RoomData data);
	Room();
	~Room() = default;
	void addUser(LoggedUser& newUser);
	void removeUser(LoggedUser& user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomMetadata();
	void setStatus(RoomStatus status);
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};