//
// Created by maria on 4/3/2023.
//

#ifndef OOP_QUESTION_H
#define OOP_QUESTION_H

#include <iostream>
#include <utility>
#include <vector>
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Timer.h"
#include "Erori.h"

class Screen {
    std::string text;
    std::vector<Button> options;

public:
    explicit Screen(std::string text = "", const std::vector<std::string> &button_options = {});

    Screen& operator=(const Screen& other) = delete;
    Screen (const Screen& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Screen& screen);

    virtual int display(sf::RenderWindow &window) = 0;

    [[nodiscard]] std::basic_string<char> getText() const;
    [[nodiscard]] std::vector<Button> getOptions() const;



    void setText(const std::string &text);

    virtual ~Screen() = 0;
};

class Question: public Screen {
protected:
    int correctAnswerIndex, category;
    float score;
public:
    explicit Question(std::string question = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0, float score_ = 1.0f);

    Question &operator=(const Question &other) = delete;

    Question (const Question &other) = delete;

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    [[nodiscard]] int getCategory() const;

    [[nodiscard]] bool checkAnswer(int userAnswer) const;

    int display(sf::RenderWindow &window) override;

    virtual float getScoreForQuestion(long long time) = 0;

    ~Question() override = default;
};




class QuestionText: public Question{

public:
    explicit QuestionText (std::string question_text = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0, float score_ = 10.0f) : Question(std::move(question_text), options, correct, category_, score_){};
    float getScoreForQuestion(long long time) override;
    static void loadQuestions(std::vector<Question *> &questions,  std::map<std::string, std::string>  &filePathNames);
    ~QuestionText() override = default;

};


class QuestionImage: public Question{
    std::string image_path;

public:
    explicit QuestionImage(std::string image = "", const std::vector<std::string> &options = {}, int correct = -1,
                           int category_ = 0, float score_ = 20.0f): Question("", options, correct, category_, score_),
                           image_path(std::move(image)){};
    int display(sf::RenderWindow &window) override;
    float getScoreForQuestion(long long time) override;
    static void loadQuestions(std::vector<Question *> &questions,  std::map<std::string, std::string>  &filePathNames);
    ~QuestionImage() override = default;

};

class MultipleAnswers: public Question{
    int correctAnswer2;
public:
    explicit MultipleAnswers(std::string question_text = "", const std::vector<std::string> &options = {},
                             int correct = -1, int correct2 = -1, int category_ = 0, float score_ = 10.0f);

    float getScoreForQuestion(long long time) override;
    static void loadQuestions(std::vector<Question *> &questions,  std::map<std::string, std::string> &filePathNames);
    int display(sf::RenderWindow &window) override;
};



class AbstractQuestionFactory {
public:
    virtual std::vector<Question*> createQuestion(std::map<std::string, std::string>& filePathNames) = 0;
    virtual ~AbstractQuestionFactory() = default;
};

class QuestionTextFactory : public AbstractQuestionFactory {
public:
    std::vector<Question *> createQuestion(std::map<std::string, std::string>& filePathNames) override;
    ~QuestionTextFactory() override = default;
};

class QuestionImageFactory : public AbstractQuestionFactory {
public:
    std::vector<Question *> createQuestion(std::map<std::string, std::string>& filePathNames) override;
    ~QuestionImageFactory() override = default;
};

class MultipleAnswersFactory : public AbstractQuestionFactory {
public:
    std::vector<Question *> createQuestion(std::map<std::string, std::string>& filePathNames) override;
    ~MultipleAnswersFactory() override = default;

};



class MenuScreen : public Screen {
    using Screen::Screen;
public:
    [[maybe_unused]] explicit MenuScreen(std::string text = "", const std::vector<std::string> &button_options = {"Next Question", "Restart"});

    MenuScreen(const MenuScreen &other) = delete;

    MenuScreen &operator=(const MenuScreen &other) = delete;

    //friend std::ostream &operator<<(std::ostream &os, const MenuScreen &screen);

    int display(sf::RenderWindow &window) override;
    ~MenuScreen() override = default;
};

class CategoryScreen : public Screen {
    using Screen::Screen;

public:
    explicit CategoryScreen(std::string text, const std::vector<std::string> &button_options = {std::string ("Music"),
                            std::string ("Geography"), std::string ("History"), std::string ("Art"),
                            std::string ("Literature"), std::string ("Sports")});

    CategoryScreen(const CategoryScreen &other) = delete;

    CategoryScreen &operator=(const CategoryScreen &other) = delete;

    //friend std::ostream &operator<<(std::ostream &os, const CategoryScreen &screen);

    int display(sf::RenderWindow &window) override;
    ~CategoryScreen() override = default;
};



class ScoreScreen: public Screen{
    using Screen::Screen;
    float score;
public:
    explicit ScoreScreen(const std::string& text = "", const std::vector<std::string> &button_options = {"Play again", "Menu", "Quit"},
                         float score_ = 0.0f);

    ScoreScreen(const ScoreScreen &other) = delete;

    ScoreScreen &operator=(const ScoreScreen &other) = delete;

    //friend std::ostream &operator<<(std::ostream &os, const ScoreScreen &screen);

    int display(sf::RenderWindow &window) override;
    ~ScoreScreen() override = default;


};


#endif //OOP_QUESTION_H
