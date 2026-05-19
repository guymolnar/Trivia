#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, unsigned int gameId) : m_questions(questions), m_gameId(gameId)
{
    for (const auto& player : players)
    {
        GameData data;
        data.currentQuestion = questions[0];
        data.correctAnswerCount = 0;
        data.wrongAnswerCount = 0;
        data.averageAnswerTime = 0;
        m_players[player] = data;
    }
}

Question Game::getQuestionForUser(const LoggedUser& user)
{
    return m_players[user].currentQuestion;
}