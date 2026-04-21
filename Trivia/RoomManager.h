#pragma once
#include <unordered_map>
#include "Room.h"

typedef int roomID;

class RoomManager {
public:
	void createRoom(LoggedUser roomAdmin, RoomData roomData);
	void deleteRoom(roomID ID);
	RoomStatus getRoomState(roomID ID);
	std::vector<RoomData> getRooms();
	Room* getRoom(roomID id);
private:
	std::unordered_map<roomID, Room> m_rooms;

};