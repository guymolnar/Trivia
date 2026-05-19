#pragma once
#include <vector>
#include <unordered_map>
#include "Question.h"
#include "LoggedUser.h"
#include "Responses.h"
#include "SqliteDataBase.h"

struct GameData
{
    Question currentQuestion;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
    unsigned int currentQuestionIndex;
    unsigned int totalAnswerTime;
};

class Game
{
public:
    Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, unsigned int gameId);

    Question getQuestionForUser(const LoggedUser& user);
    std::unordered_map<LoggedUser, GameData> getPlayers();
    void submitAnswer(const LoggedUser& user, unsigned int answerId, unsigned int answerTime);
    void removePlayer(const LoggedUser& user);
    void submitStatsToDB(const GameData& data, const std::string& username);

private:
    std::vector<Question> m_questions;
    std::unordered_map<LoggedUser, GameData> m_players;
    unsigned int m_gameId;
};