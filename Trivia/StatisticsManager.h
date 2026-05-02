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
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;
private:
    StatisticsManager() = default;
	//Database is a singleton so no m_database
};
