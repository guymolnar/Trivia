#include "Room.h"

Room::Room(RoomData data) : m_metadata(data)
{

}

Room::Room() : m_metadata()
{
}

void Room::addUser(LoggedUser& newUser)
{
	m_users.push_back(newUser);
}

void Room::removeUser(LoggedUser& user)
{
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
    std::vector<std::string> names;
    for (auto& user : m_users)
    {
        names.push_back(user.getUsername());
    }
    return names;
}

RoomData Room::getRoomMetadata()
{
    return m_metadata;
}

void Room::setStatus(RoomStatus status)
{
    m_metadata.status = status;
}