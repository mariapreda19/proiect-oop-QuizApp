//
// Created by maria on 4/3/2023.
//

#ifndef OOP_QUESTION_H
#define OOP_QUESTION_H

#include <iostream>
#include <vector>

class Screen {
    std::string text;
    std::vector<std::string> options;

public:
    explicit Screen(std::string text = "", const std::vector<std::string> &options = {});

    friend std::ostream& operator<<(std::ostream& os, const Screen& screen);
};


class Question {
private:
    std::string questionText;
    std::vector<std::string> answerOptions;
    int correctAnswerIndex;
    int level;

public:
    explicit Question(std::string question = "", const std::vector<std::string> &options = {}, int correct = -1, int level_ = 0);

    Question(const Question &other);

    Question &operator=(const Question &other);

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    [[nodiscard]] int getLevel() const;

    void printQuestion() const;

    [[nodiscard]] bool checkAnswer(int userAnswer) const;

    [[nodiscard]] bool askQuestion() const;
};


#endif //OOP_QUESTION_H
