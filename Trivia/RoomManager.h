#pragma once
#include <unordered_map>
#include "Room.h"

class RoomManager {
public:
	static RoomManager& getInstance()
	{
		static RoomManager instance;
		return instance;
	}
	RoomManager(const RoomManager&) = delete;
	void operator=(const RoomManager&) = delete;
	unsigned int createRoom(LoggedUser roomAdmin, RoomData roomData);
	void deleteRoom(unsigned int id);
	RoomStatus getRoomState(unsigned int id);
	std::vector<RoomData> getRooms();
	Room* getRoom(unsigned int id);
private:
	RoomManager() = default;
	std::unordered_map<unsigned int, Room> m_rooms;
	unsigned int m_nextRoomId = 0;

};