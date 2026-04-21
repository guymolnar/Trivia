#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser roomAdmin, RoomData roomData)
{
    Room newRoom(roomData);
    newRoom.addUser(roomAdmin);
    m_rooms[roomData.id] = newRoom;
}

void RoomManager::deleteRoom(roomID ID)
{
    m_rooms.erase(ID);
}

Room* RoomManager::getRoom(roomID ID)
{
    auto it = m_rooms.find(ID);
    if (it == m_rooms.end())
    {
        return nullptr;
    }
    return &it->second;
}

RoomStatus RoomManager::getRoomState(roomID ID)
{
    Room* r = getRoom(ID);
    if (!r)
    {
        throw std::exception("Room does not exist");
    }
    return r->getRoomStatus();
}