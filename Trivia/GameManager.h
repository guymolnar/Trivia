#pragma once
#include <list>
#include <string>
#include "SqliteDataBase.h"
#include "Game.h"

class GameManager
{
public:
    static GameManager& getInstance()
    {
        static GameManager instance;
        return instance;
    }

    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    ~GameManager() = default;
    Game& createGame(Room& room);
    Game& getGame(unsigned int gameId);
    void deleteGame(unsigned int gameId);
private:
    GameManager() = default;
    std::list<Game> m_games;
    //Database is a singleton so no m_database
};
