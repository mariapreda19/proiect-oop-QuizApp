//
// Created by maria on 4/3/2023.
//

#include "../headers/Question.h"


Screen::Screen(std::string text, const std::vector<std::string> &options) : text(std::move(text)), options(options){}

std::ostream& operator<<(std::ostream& os, const Screen& screen) {
    os << "Text: " << screen.text << std::endl;
    os << "Options:" << std::endl;
    for (long long unsigned int i = 0; i < screen.options.size(); i++) {
        os << i + 1 << ". " << screen.options[i] << std::endl;
    }
}


Question::Question(std::string  question, const std::vector<std::string>& options, const int correct, const int level_) :
        questionText(std::move(question)), answerOptions(options), correctAnswerIndex(correct), level(level_){
}

Question::Question(const Question& other) :
        questionText(other.questionText),
        answerOptions(other.answerOptions),
        correctAnswerIndex(other.correctAnswerIndex),
        level(other.level){}

Question& Question::operator=(const Question& other) = default;

std::ostream& operator<<(std::ostream& os, const Question& question) {
    os << "Question: " << question.questionText << std::endl;
    os << "Answer options:" << std::endl;
    for (long long unsigned int i = 0; i < question.answerOptions.size(); i++) {
        os << i+1 << ". " << question.answerOptions[i] << std::endl;
    }
    os << "Correct answer: " << question.answerOptions[question.correctAnswerIndex] << std::endl;
    return os;
}

//[[nodiscard]] int getCorrectAnswerIndex() const {return correctAnswerIndex;}
//[[nodiscard]] std::vector<std::string> getAnswerText() const {return answerOptions;}
//[[nodiscard]] std::string getQuestionText() const {return questionText;}
[[nodiscard]] int Question::getLevel() const {return level;}

void Question::printQuestion() const {
    std::cout << questionText << std::endl;

    for (long long unsigned int i = 0; i < answerOptions.size(); i++) {
        std::cout << i+1 << ". " << answerOptions[i] << std::endl;
    }
}
[[nodiscard]] bool Question::checkAnswer(int userAnswer) const {
    return (userAnswer == correctAnswerIndex);
}

[[nodiscard]] bool Question::askQuestion() const {
    printQuestion();

    int userAnswer;
    std::cout << "Enter your answer: ";
    std::cin >> userAnswer;

    if (checkAnswer(userAnswer - 1)) {
        std::cout << "Correct!" << std::endl;
        return true;
    } else {
        std::cout << "Incorrect." << std::endl;
        return false;
    }
}
