#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser roomAdmin, RoomData roomData)
{
    Room newRoom(roomData);
    newRoom.addUser(roomAdmin);
    m_rooms[roomData.id] = newRoom;
}