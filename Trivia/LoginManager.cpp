#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* IDB) : m_database(IDB)
{

}

LoginManager::~LoginManager()
{

}

void LoginManager::signup(const std::string& name, const std::string& password, const std::string& mail, const std::string& address, const std::string& phone, const std::string& birthday)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_database->doesUserExist(name))
    {
        throw std::exception("User already exists");
    }
    m_database->addNewUser(name, password, mail, address, phone, birthday);
    m_loggedUsers.push_back(LoggedUser(name));
}

void LoginManager::login(const std::string& name, const std::string& password)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& user : m_loggedUsers)
    {
        if (user.getUsername() == name)
        {
            throw std::exception("User already logged in");
        }
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

void LoginManager::logout(const std::string& name)
{
    std::lock_guard<std::mutex> lock(m_mutex);
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