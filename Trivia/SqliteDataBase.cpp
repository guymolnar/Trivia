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
    const char* createTable = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, email TEXT, address TEXT, phone TEXT, birthday TEXT);";
    sqlite3_exec(m_db, createTable, nullptr, nullptr, nullptr);

    std::string createQuestionsTable = "CREATE TABLE IF NOT EXISTS questions (id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT NOT NULL, answer1 TEXT NOT NULL, answer2 TEXT NOT NULL, answer3 TEXT NOT NULL, answer4 TEXT NOT NULL, correctAnswerId INTEGER NOT NULL);";
    sqlite3_exec(m_db, createQuestionsTable.c_str(), nullptr, nullptr, nullptr);

    std::string createStatisticsTable = "CREATE TABLE IF NOT EXISTS statistics (username TEXT PRIMARY KEY, totalCorrectAnswers INTEGER DEFAULT 0, totalWrongAnswers INTEGER DEFAULT 0, totalAnswerTime REAL DEFAULT 0, totalAnswers INTEGER DEFAULT 0, numOfGames INTEGER DEFAULT 0); ";
    sqlite3_exec(m_db, createStatisticsTable.c_str(), nullptr, nullptr, nullptr);
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

int SqliteDataBase::addNewUser(std::string username, std::string password, std::string email, std::string address, std::string phone, std::string birthday)
{
    std::string query = "INSERT INTO users (username, password, email, address, phone, birthday) VALUES ('" + username + "', '" + password + "', '" + email + "', '" + address + "', '" + phone + "', '" + birthday + "');";
    return sqlite3_exec(m_db, query.c_str(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

std::vector<Question> SqliteDataBase::getQuestions(int numOfQuestions)
{
    std::vector<Question> questions;
    std::string query = "SELECT question, answer1, answer2, answer3, answer4, correctAnswerId FROM questions ORDER BY RANDOM() LIMIT " + std::to_string(numOfQuestions) + ";";

    sqlite3_exec(m_db, query.c_str(), [](void* data, int, char** argv, char**) {
        auto* questions = reinterpret_cast<std::vector<Question>*>(data);
        std::string question = argv[0];
        std::vector<std::string> answers = { argv[1], argv[2], argv[3], argv[4] };
        int correctAnswerId = std::stoi(argv[5]);
        questions->push_back(Question(question, answers, correctAnswerId));
        return 0;
        }, &questions, nullptr);

    return questions;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
    std::string query = "SELECT totalAnswerTime, totalAnswers FROM statistics WHERE username = '" + username + "';";
    std::pair<float, int> data = { 0, 0 };
    sqlite3_exec(m_db, query.c_str(), [](void* d, int, char** argv, char**) {
        auto* p = reinterpret_cast<std::pair<float, int>*>(d);
        p->first = std::stof(argv[0]);
        p->second = std::stoi(argv[1]);
        return 0;
        }, &data, nullptr);
    return data.second > 0 ? data.first / data.second : 0;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
    return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
    return 0;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
    return 0;
}

int SqliteDataBase::getPlayerScore(std::string username)
{
    return 0;
}

std::vector<std::string> SqliteDataBase::getHighScores()
{
    return {};
}