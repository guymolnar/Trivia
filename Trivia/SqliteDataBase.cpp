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