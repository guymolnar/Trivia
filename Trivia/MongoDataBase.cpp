#include "MongoDataBase.h"

MongoDataBase::MongoDataBase() :m_instance{}, m_client{ mongocxx::uri{"mongodb://localhost:27017"} }, m_db{ m_client["trivia"] }
{
}

bool MongoDataBase::open()
{
    return true;
}

bool MongoDataBase::close()
{
    return true;
}

int MongoDataBase::doesUserExist(std::string username)
{
    auto collection = m_db["users"];
    auto result = collection.find_one(document{} << "username" << username << finalize
    );
    return result ? 1 : 0;
}

int MongoDataBase::doesPasswordMatch(std::string username, std::string password)
{
    auto collection = m_db["users"];
    auto result = collection.find_one(
        document{} << "username" << username << "password" << password << finalize
    );
    return result ? 1 : 0;
}

int MongoDataBase::addNewUser(std::string username, std::string password, std::string email,
    std::string address, std::string phone, std::string birthday)
{
    auto collection = m_db["users"];
    auto doc = document{}
        << "username" << username
        << "password" << password
        << "email" << email
        << "address" << address
        << "phone" << phone
        << "birthday" << birthday
        << finalize;
    auto result = collection.insert_one(doc.view());
    return result ? 1 : 0;
}