//
// Created by maria on 4/3/2023.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H
#include "SFML/Graphics.hpp"


class Button{
    sf::Vector2f position;
    std::string buttonTexture; // path to texture

public:
    Button (sf::Vector2f position_, std::string texture_);

    Button(const Button& other);

    Button& operator=(const Button& other);

    ~Button();

    bool displayButton(sf::RenderWindow &window);

};


#endif //OOP_BUTTON_H
