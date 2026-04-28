#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
class LoginManager {
public:
	static LoginManager& getInstance(IDatabase* IDB)
	{
		static LoginManager instance(IDB);
		return instance;
	}
	LoginManager(const LoginManager&) = delete;
	void operator=(const LoginManager&) = delete;
	~LoginManager();

	void signup(std::string name, std::string password, std::string mail, std::string address, std::string phone, std::string birthday);
	void login(std::string name, std::string password);
	void logout(std::string name);
private:
	LoginManager(IDatabase* IDB);
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};