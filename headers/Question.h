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

    virtual ~Screen() = default;
};



class Question: public Screen {

    using Screen::Screen;
    int correctAnswerIndex, category;
public:
    explicit Question(std::string question = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0);

    Question &operator=(const Question &other) = delete;

    Question (const Question &other) = delete;

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    [[nodiscard]] int getCategory() const;

    [[nodiscard]] bool checkAnswer(int userAnswer) const;

    int display(sf::RenderWindow &window) override;

    ~Question() override = default;
};

class QuestionText: public Question{
    using Question::Question;

public:
    explicit QuestionText (std::string question_text = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0) : Question(std::move(question_text), options, correct, category_){};
    ~QuestionText() override = default;
};
class QuestionImage: public Question{
    std::string image_path;
    using Question::Question;

public:
    explicit QuestionImage(std::string image = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0): Question("", options, correct, category_), image_path(std::move(image)){};
    int display(sf::RenderWindow &window) override;
    ~QuestionImage() override = default;
};

class MenuScreen : public Screen {
    using Screen::Screen;
public:
    explicit MenuScreen(std::string text = "", const std::vector<std::string> &button_options = {"Next Question", "Restart"});

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
    int score;
public:
    explicit ScoreScreen(const std::string& text = "", const std::vector<std::string> &button_options = {"Play again", "Menu", "Quit"},
                         int score_ = 0);

    ScoreScreen(const ScoreScreen &other) = delete;

    ScoreScreen &operator=(const ScoreScreen &other) = delete;

    //friend std::ostream &operator<<(std::ostream &os, const ScoreScreen &screen);

    int display(sf::RenderWindow &window) override;
    ~ScoreScreen() override = default;


};



#endif //OOP_QUESTION_H
