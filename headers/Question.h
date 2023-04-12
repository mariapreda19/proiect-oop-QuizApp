//
// Created by maria on 4/3/2023.
//

#ifndef OOP_QUESTION_H
#define OOP_QUESTION_H

#include <iostream>
#include <vector>
#include "Button.h"
#include "SFML/Graphics.hpp"

class Screen {
    std::string text;
    std::vector<Button> options;

public:
    explicit Screen(std::string text = "", const std::vector<std::string> &button_options = {});

    friend std::ostream& operator<<(std::ostream& os, const Screen& screen);

    int displayScreen(sf::RenderWindow &window);
};

class Question: public Screen {

    using Screen::Screen;
    int correctAnswerIndex, category;

public:
    explicit Question(std::string question = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0);

    Question(const Question &other);

    Question &operator=(const Question &other);

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    [[nodiscard]] int getCategory() const;

//    void printQuestion() const;

    [[nodiscard]] bool checkAnswer(int userAnswer) const;

    [[nodiscard]] bool askQuestion() const;
};

class Menu: public Screen{
    using Screen::Screen;
    Button single, competitive;

private:
    explicit Menu(std::string text = "", const std::vector<std::string> &button_options = {},
                  std::string button_texture = "", std::string button_texture_clicked = "");
    Menu(const Menu &other);
    Menu &operator=(const Menu &other);
};


#endif //OOP_QUESTION_H
