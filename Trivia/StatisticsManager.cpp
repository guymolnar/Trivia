#include "StatisticsManager.h"

std::vector<std::string> getHighScore()
{
	return SqliteDataBase::getInstance().getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    IDatabase& db = SqliteDataBase::getInstance();

    std::vector<std::string> stats;
    stats.push_back("Average answer time: " + std::to_string(db.getPlayerAverageAnswerTime(username)));
    stats.push_back("Correct answers: " + std::to_string(db.getNumOfCorrectAnswers(username)));
    stats.push_back("Total answers: " + std::to_string(db.getNumOfTotalAnswers(username)));
    stats.push_back("Games played: " + std::to_string(db.getNumOfPlayerGames(username)));
    stats.push_back("Score: " + std::to_string(db.getPlayerScore(username)));

    return stats;
}