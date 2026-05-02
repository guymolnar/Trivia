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

	void signup(const std::string& name, const std::string& password, const std::string& mail, const std::string& address, const std::string& phone, const std::string& birthday);
	void login(const std::string& name, const std::string& password);
	void logout(const std::string& name);
private:
	LoginManager(IDatabase* IDB);
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};