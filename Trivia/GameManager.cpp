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