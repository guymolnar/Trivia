#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
class LoginManager {
public:
	void signup(std::string, std::string, std::string);
	void login(std::string, std::string);
	void logout(std::string);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUser;
};