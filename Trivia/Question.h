#pragma once
#include <string>
#include <list>
#include <vector>

class Question {
public:
	Question(std::string question, std::vector<std::string> possibleAnswers, int correctAnswerId);
	Question() = default;
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correctAnswerId;
};