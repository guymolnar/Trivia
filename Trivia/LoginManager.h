#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
class LoginManager {
public:
	LoginManager(IDatabase* IDB);
	~LoginManager();

	void signup(std::string name, std::string password, std::string mail);
	void login(std::string name, std::string password);
	void logout(std::string name);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};