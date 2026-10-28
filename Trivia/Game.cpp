#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, unsigned int gameId)
    : m_questions(questions), m_gameId(gameId)
{
    for (const auto& player : players)
    {
        GameData data;
        data.currentQuestion = questions[0];
        data.correctAnswerCount = 0;
        data.wrongAnswerCount = 0;
        data.averageAnswerTime = 0;
        data.currentQuestionIndex = 0;
        data.totalAnswerTime = 0;
        m_players[player] = data;
    }
}

unsigned int Game::getGameId() const
{
    return m_gameId;
}

Question Game::getQuestionForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_players[user].currentQuestion;
}

std::map<LoggedUser, GameData> Game::getPlayers()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_players;
}

void Game::submitAnswer(const LoggedUser& user, unsigned int answerId, unsigned int answerTime)
{
    std::lock_guard<std::mutex> lock(m_mutex);
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
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_players[user].currentQuestionIndex >= m_questions.size())
    {
        return;
    }
    submitStatsToDB(m_players[user], user.getUsername());
    m_players[user].currentQuestionIndex = m_questions.size();
}

void Game::submitStatsToDB(const GameData& data, const std::string& username)
{
    SqliteDataBase::getInstance().submitGameStatistics(username, data.correctAnswerCount, data.wrongAnswerCount, data.averageAnswerTime);
}

bool Game::hasFinished(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_players[user].currentQuestionIndex >= m_questions.size();
}

void Game::submitStatsForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    submitStatsToDB(m_players[user], user.getUsername());
}

bool Game::allPlayersFinished()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (const auto& [user, data] : m_players)
    {
        if (data.currentQuestionIndex < m_questions.size())
        {
            return false;
        }
    }
    return true;
}