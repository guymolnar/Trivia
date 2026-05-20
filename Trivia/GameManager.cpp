#include "GameManager.h"

Game& GameManager::createGame(Room& room)
{
    RoomData meta = room.getRoomMetadata();
    std::vector<Question> questions = SqliteDataBase::getInstance().getQuestions(meta.numOfQuestions);

    std::vector<std::string> usernames = room.getAllUsers();
    std::vector<LoggedUser> players;
    for (const auto& username : usernames)
    {
        players.push_back(LoggedUser(username));
    }

    m_games.push_back(Game(questions, players, meta.id));
    return m_games.back();
}

Game& GameManager::getGame(unsigned int gameId)
{
    for (auto& game : m_games)
    {
        if (game.getGameId() == gameId)
            return game;
    }
    throw std::exception("Game not found");
}

void GameManager::deleteGame(unsigned int gameId)
{
    for (auto it = m_games.begin(); it != m_games.end(); ++it)
    {
        if (it->getGameId() == gameId)
        {
            m_games.erase(it);
            return;
        }
    }
}