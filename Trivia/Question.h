#pragma once
#include <string>
#include <list>
#include <vector>

class Question {
public:
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers;
	int getCorrectAnswerId();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};