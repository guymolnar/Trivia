#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* IDB) : m_database(IDB)
{

}

LoginManager::~LoginManager()
{

}

void LoginManager::signup(std::string name, std::string password, std::string mail)
{
    if (m_database->doesUserExist(name))
    {
        throw std::exception("User already exists");
    }
    m_database->addNewUser(name, password, mail);
}

void LoginManager::login(std::string name, std::string password)
{
    for (auto& user : m_loggedUsers)
    {
        if (user.getUsername() == name)
            throw std::exception("User already logged in");
    }
    if (!m_database->doesUserExist(name))
    {
        throw std::exception("User does not exist");
    }
    if (!m_database->doesPasswordMatch(name, password))
    {
        throw std::exception("Wrong password");
    }
    m_loggedUsers.push_back(LoggedUser(name));
}

void LoginManager::logout(std::string name)
{
    if (!m_database->doesUserExist(name))
    {
        throw std::exception("User does not exist");
    }
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
    {
        if (it->getUsername() == name)
        {
            m_loggedUsers.erase(it);
            break;
        }
    }
}