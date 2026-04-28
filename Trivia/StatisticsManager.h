#pragma once
#include <vector>
#include <string>
#include "SqliteDataBase.h"

class StatisticsManager
{
public:
    static StatisticsManager& getInstance()
    {
        static StatisticsManager instance;
        return instance;
    }

    StatisticsManager(const StatisticsManager&) = delete;
    void operator=(const StatisticsManager&) = delete;

	~StatisticsManager() = default;
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
private:
    StatisticsManager() = default;
	//Database is a singleton so no m_database
};
