#include "Room.h"

Room::Room(RoomData data) : m_metadata(data)
{

}

Room::Room() : m_metadata()
{
}

void Room::addUser(LoggedUser& newUser)
{
    std::lock_guard<std::mutex> lock(m_mutex);
	m_users.push_back(newUser);
}

void Room::removeUser(LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if (it->getUsername() == user.getUsername())
        {
            m_users.erase(it);
            break;
        }
    }
}

std::vector<std::string> Room::getAllUsers()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::string> names;
    for (auto& user : m_users)
    {
        names.push_back(user.getUsername());
    }
    return names;
}

RoomData Room::getRoomMetadata()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_metadata;
}

void Room::setStatus(RoomStatus status)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_metadata.status = status;
}