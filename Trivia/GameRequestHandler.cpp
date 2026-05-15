#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game, GameManager& gameManager) : m_handlerFactory(handlerFactory),
m_user(user), m_game(game), m_gameManager(gameManager)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    return requestInfo.id == LEAVE_GAME_REQUEST_CODE ||
        requestInfo.id == GET_QUESTION_REQUEST_CODE ||
        requestInfo.id == SUBMIT_ANSWER_REQUEST_CODE ||
        requestInfo.id == GET_GAME_RESULTS_REQUEST_CODE;
}

LoggedUser* GameRequestHandler::getLoggedUser()
{
    return &m_user;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    if (requestInfo.id == LEAVE_GAME_REQUEST_CODE)
    {
        return leaveGame(requestInfo);
    }
    if (requestInfo.id == GET_QUESTION_REQUEST_CODE)
    {
        return getQuestion(requestInfo);
    }
    if (requestInfo.id == SUBMIT_ANSWER_REQUEST_CODE)
    {
        return submitAnswer(requestInfo);
    }
    if (requestInfo.id == GET_GAME_RESULTS_REQUEST_CODE)
    {
        return getGameResults(requestInfo);
    }

    ErrorResponse err{ "Request not relevant to GameRequestHandler" };
    return { JsonResponsePacketSerializer::serializeResponse(err), this };
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo)
{
    try
    {
        Question question = m_game.getQuestionForUser(m_user);
        std::vector<std::string> answersList = question.getPossibleAnswers();
        std::unordered_map<unsigned int, std::string> answersMap;
        for (unsigned int i = 0; i < answersList.size(); i++)
        {
            answersMap[i + 1] = answersList[i];
        }
        GetQuestionResponse response{ 1, question.getQuestion(), answersMap };
        return { JsonResponsePacketSerializer::serializeResponse(response), this };
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo)
{
    try
    {
        SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
        m_game.submitAnswer(m_user, request.answerId);
        Question question = m_game.getQuestionForUser(m_user);
        SubmitAnswerResponse response;
        response.status = 1;
        response.correctAnswerId = question.getCorrectAnswerId();

        return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response), this};
    }
    catch (const std::exception& e)
    {
        ErrorResponse err{ e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}