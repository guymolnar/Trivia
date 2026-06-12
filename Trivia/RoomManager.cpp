
#include "RoomManager.h"

unsigned int RoomManager::createRoom(LoggedUser roomAdmin, RoomData roomData)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    roomData.id = m_nextRoomId++;
    Room newRoom(roomData);
    newRoom.addUser(roomAdmin);
    m_rooms[roomData.id] = newRoom;
    return roomData.id;
}

void RoomManager::deleteRoom(unsigned int id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_rooms.erase(id);
}

Room* RoomManager::getRoom(unsigned int id)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = m_rooms.find(id);
    if (it == m_rooms.end())
    {
        return nullptr;
    }
    return &it->second;
}

RoomStatus RoomManager::getRoomState(unsigned int id)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    Room* r = getRoom(id);
    if (!r)
    {
        throw std::exception("Room does not exist");
    }
    return r->getRoomMetadata().status;
}

std::vector<RoomData> RoomManager::getRooms()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::vector<RoomData> roomsVector;
    for (auto& [id, room] : m_rooms)
    {
        if(room.getRoomMetadata().status == INACTIVE)
        {
            roomsVector.push_back(room.getRoomMetadata());
        }
    }
    return roomsVector;
}