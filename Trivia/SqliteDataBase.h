#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include <string>

class SqliteDataBase : public IDatabase {
public:
    static SqliteDataBase& getInstance()
    {
        static SqliteDataBase instance;
        return instance;
    }
    SqliteDataBase(const SqliteDataBase&) = delete;
    void operator=(const SqliteDataBase&) = delete;
    ~SqliteDataBase();
    bool open() override;
    bool close() override;
    int doesUserExist(std::string username) override;
    int doesPasswordMatch(std::string username, std::string password) override;
    int addNewUser(std::string username, std::string password, std::string email, std::string address, std::string phone, std::string birthday) override;
    std::vector<Question> getQuestions(int numOfQuestions) override;
    float getPlayerAverageAnswerTime(std::string username) override;
    int getNumOfCorrectAnswers(std::string username) override;
    int getNumOfTotalAnswers(std::string username) override;
    int getNumOfPlayerGames(std::string username) override;
    int getPlayerScore(std::string username) override;
    std::vector<std::string> getHighScores() override;
private:
    SqliteDataBase();
    sqlite3* m_db;
};