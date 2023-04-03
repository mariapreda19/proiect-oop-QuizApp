//
// Created by maria on 4/3/2023.
//

#include "../headers/Button.h"


Button::Button (sf::Vector2f position_, std::string texture_) : position(position_), buttonTexture(std::move(texture_)) {}

Button::Button(const Button& other): position(other.position), buttonTexture(other.buttonTexture){}

Button& Button::operator=(const Button& other) = default;

Button::~Button() = default;

bool Button::displayButton(sf::RenderWindow &window){
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile(this -> buttonTexture);
    sprite.setTexture(texture);
    sprite.setPosition(this -> position);
    window.draw(sprite);
    sf::Vector2f tempMouse(sf::Mouse::getPosition(window));
    if( sprite.getGlobalBounds().contains(tempMouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        while (sprite.getGlobalBounds().contains(tempMouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
        return true;
    }
    return false;
}

