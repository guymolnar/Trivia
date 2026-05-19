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

void Game::submitAnswer(const LoggedUser& user, unsigned int answerId, unsigned int answerTime)
{
    GameData& data = m_players[user];

    if (answerId == static_cast<unsigned int>(data.currentQuestion.getCorrectAnswerId()))
    {
        data.correctAnswerCount++;
    }
    else
    {
        data.wrongAnswerCount++;
    }

    data.totalAnswerTime += answerTime;
    unsigned int totalAnswered = data.correctAnswerCount + data.wrongAnswerCount;
    data.averageAnswerTime = data.totalAnswerTime / totalAnswered;

    data.currentQuestionIndex++;
    if (data.currentQuestionIndex < m_questions.size())
    {
        data.currentQuestion = m_questions[data.currentQuestionIndex];
    }
}

void Game::removePlayer(const LoggedUser& user)
{
}