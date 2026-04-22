#pragma once
#include <vector>
#include <string>

class StatisticsManager
{
public:
	StatisticsManager() = default;
	~StatisticsManager() = default;
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
private:
	//Database is a singleton so no m_database
};
