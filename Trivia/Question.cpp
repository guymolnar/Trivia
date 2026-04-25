#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, int correctAnswerId) : m_question(question), m_possibleAnswers(possibleAnswers), m_correctAnswerId(correctAnswerId)
{
}

std::string Question::getQuestion()
{
    return m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
    return m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
    return m_correctAnswerId;
}