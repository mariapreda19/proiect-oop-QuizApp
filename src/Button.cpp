//
// Created by maria on 4/3/2023.
//

#include <utility>
#include "../headers/Button.h"


Button::Button (std::string text, std::string texture_) : text(std::move(text)), texture(std::move(texture_)) {}

Button::Button(const Button& other) = default;

Button& Button::operator=(const Button& other) = default;

Button::~Button() = default;

bool Button::displayButton(sf::RenderWindow &window, sf::Vector2f position){
    sf::Sprite sprite;
    sf::Texture texture_;
    sf::Text text_;
    sf::Font font;
    font.loadFromFile("arial.ttf");

    text_.setString(this -> text);
    text_.setCharacterSize(20);
    text_.setFont(font);
    text_.setFillColor(sf::Color::White);

    texture_.loadFromFile(this -> texture);
    sprite.setTexture(texture_);
    sprite.setPosition(position);

    sf::Vector2f textPosition = {position.x + (float(texture_.getSize().x) - text_.getGlobalBounds().getSize().x) / 2,
                                 position.y + (float(texture_.getSize().y) - text_.getGlobalBounds().getSize().y) / 2};

    text_.setPosition(textPosition);

    window.draw(sprite);
    window.draw(text_);

    sf::Vector2f tempMouse(sf::Mouse::getPosition(window));
    if( sprite.getGlobalBounds().contains(tempMouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        while (sprite.getGlobalBounds().contains(tempMouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Button &button) {
    os << ' ' << button.text;
    return os;
}

