//
// Created by maria on 4/3/2023.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H
#include "SFML/Graphics.hpp"


class Button{
    std::string text;
    std::string texture; // path to texture

public:
    Button (std::string text, std::string texture_);

    Button(const Button& other);

    Button& operator=(const Button& other);

    ~Button();

    bool displayButton(sf::RenderWindow &window, sf::Vector2f position);

    friend std::ostream& operator<<(std::ostream& os, const Button& button);

};


#endif //OOP_BUTTON_H
