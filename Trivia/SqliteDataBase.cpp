#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase() : m_db(nullptr) 
{
}

SqliteDataBase::~SqliteDataBase() 
{ 
    close(); 
}

bool SqliteDataBase::open()
{
    if (sqlite3_open("trivia.db", &m_db) != SQLITE_OK)
    {
        return false;
    }
    const char* createTable = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, email TEXT);";
    sqlite3_exec(m_db, createTable, nullptr, nullptr, nullptr);
    return true;
}

bool SqliteDataBase::close()
{
    if (m_db) 
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
    return true;
}

int SqliteDataBase::doesUserExist(std::string username)
{
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "';";
    int count = 0;
    sqlite3_exec(m_db, query.c_str(), [](void* data, int, char** argv, char**) {
        *reinterpret_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
        }, &count, nullptr);
    return count;
}

int SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "' AND password = '" + password + "';";
    int count = 0;
    sqlite3_exec(m_db, query.c_str(), [](void* data, int, char** argv, char**) {
        *reinterpret_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
        }, &count, nullptr);
    return count;
}

int SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
    std::string query = "INSERT INTO users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "');";
    return sqlite3_exec(m_db, query.c_str(), nullptr, nullptr, nullptr) == SQLITE_OK;
}