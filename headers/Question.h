//
// Created by maria on 4/3/2023.
//

#ifndef OOP_QUESTION_H
#define OOP_QUESTION_H

#include <iostream>
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

    friend std::ostream& operator<<(std::ostream& os, const Screen& screen);

    virtual int display(sf::RenderWindow &window) = 0;

    [[nodiscard]] std::basic_string<char> getText() const;
    [[nodiscard]] std::vector<Button> getOptions() const;

    virtual ~Screen();

};



class Question: public Screen {

    using Screen::Screen;
    int correctAnswerIndex, category;
public:
    explicit Question(std::string question = "", const std::vector<std::string> &options = {}, int correct = -1, int category_ = 0);

    Question &operator=(const Question &other);

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    [[nodiscard]] int getCategory() const;

    [[nodiscard]] bool checkAnswer(int userAnswer) const;

    int display(sf::RenderWindow &window) override;


};


class MenuScreen : public Screen {
    using Screen::Screen;
public:
    //explicit MenuScreen(std::string text = "", const std::vector<std::string> &button_options = {"Play again", "Menu", "Quit"});

    //MenuScreen(const MenuScreen &other);

    MenuScreen &operator=(const MenuScreen &other);

    //friend std::ostream &operator<<(std::ostream &os, const MenuScreen &screen);



    int display(sf::RenderWindow &window) override;
};

class CategoryScreen : public Screen {
    using Screen::Screen;

public:
    explicit CategoryScreen(std::string text, const std::vector<std::string> &button_options = {std::string ("Music"), std::string ("Geography"), std::string ("History"), std::string ("Art"), std::string ("Literature"), std::string ("Sports")});

    //CategoryScreen(const CategoryScreen &other);

    CategoryScreen &operator=(const CategoryScreen &other);

    //friend std::ostream &operator<<(std::ostream &os, const CategoryScreen &screen);

    int display(sf::RenderWindow &window) override;
};
#endif //OOP_QUESTION_H
