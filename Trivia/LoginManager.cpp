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
    if (!m_database->doesUserExist(name))
    {
        throw std::exception("User does not exist");
    }
    if (!m_database->doesPasswordMatch(name, password))
    {
        throw std::exception("Wrong password");
    }
    m_loggedUser.push_back(LoggedUser(name));
}