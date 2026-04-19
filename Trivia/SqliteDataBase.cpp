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
    return sqlite3_open("trivia.db", &m_db) == SQLITE_OK;
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
