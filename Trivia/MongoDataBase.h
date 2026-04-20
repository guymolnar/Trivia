#pragma once
#include "IDatabase.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>

using bsoncxx::v_noabi::builder::stream::document;
using bsoncxx::v_noabi::builder::stream::finalize;

class MongoDataBase : public IDatabase {
public:
    static MongoDataBase& getInstance()
    {
        static MongoDataBase instance;
        return instance;
    }

    MongoDataBase(const MongoDataBase&) = delete;
    void operator=(const MongoDataBase&) = delete;

    bool open() override;
    bool close() override;
    int doesUserExist(std::string username) override;
    int doesPasswordMatch(std::string username, std::string password) override;
    int addNewUser(std::string username, std::string password, std::string email,
        std::string address, std::string phone, std::string birthday) override;

private:
    MongoDataBase();
    mongocxx::instance m_instance;
    mongocxx::client m_client;
    mongocxx::database m_db;
};