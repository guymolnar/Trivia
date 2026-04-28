#pragma once
#include <unordered_map>
#include "Room.h"

typedef int roomID;

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
	void deleteRoom(roomID ID);
	RoomStatus getRoomState(roomID ID);
	std::vector<RoomData> getRooms();
	Room* getRoom(roomID id);
private:
	RoomManager() = default;
	std::unordered_map<roomID, Room> m_rooms;
	unsigned int m_nextRoomId = 0;

};