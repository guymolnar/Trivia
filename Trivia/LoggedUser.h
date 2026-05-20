#pragma once
#include <string>

class LoggedUser {
public:
	LoggedUser(std::string username);
	~LoggedUser() = default;
	std::string getUsername() const;
	bool operator<(const LoggedUser& other) const  
	{
		return m_username < other.m_username;
	}
private:
	std::string m_username;
};