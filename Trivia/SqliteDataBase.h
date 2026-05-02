#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include "Question.h"
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
    int doesUserExist(const std::string& username) override;
    int doesPasswordMatch(const std::string& username, const std::string& password) override;
    int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phone, const std::string& birthday) override;
    std::vector<Question> getQuestions(int numOfQuestions) override;
    float getPlayerAverageAnswerTime(const std::string& username) override;
    int getNumOfCorrectAnswers(const std::string& username) override;
    int getNumOfTotalAnswers(const std::string& username) override;
    int getNumOfPlayerGames(const std::string& username) override;
    int getPlayerScore(const std::string& username) override;
    std::vector<std::string> getHighScores() override;
private:
    SqliteDataBase();
    sqlite3* m_db;
    const char* DB_NAME = "trivia.db";
};