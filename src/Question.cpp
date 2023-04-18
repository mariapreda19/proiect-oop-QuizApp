//
// Created by maria on 4/3/2023.
//

#include <utility>

#include "../headers/Question.h"


Screen::Screen(std::string text, const std::vector<std::string> &button_options) : text(std::move(text)){

    unsigned long long int size_ = button_options.size();

    float space_left = float(1000 - (196 * int(size_ / 2) + 20 * (int(size_ / 2) - 1))) / 2;
    //TODO edit this after final textures are added;

    for(unsigned long long int i=0; i < size_ ; i++){
        Button temp({space_left + float(i % (size_ / 2)) * 216, 400 + float(int(i / (size_ / 2))) * 138}, button_options[i] ,"button.png");
        options.emplace_back(temp);
    }

}

std::ostream& operator<<(std::ostream& os, const Screen& screen) {
    os << "Text: " << screen.text << std::endl;
    os << "Options:" << std::endl;

    for (long long unsigned int i = 0; i < screen.options.size(); i++) {
        os << i + 1 << ". " << screen.options[i] << std::endl;
    }
    return os;
}


int Screen::displayScreen (sf::RenderWindow &window){

    sf::Sprite box;
    sf::Texture texture;
    texture.loadFromFile("rectangle.png");
    box.setTexture(texture);
    box.setPosition(100, 100);

    sf::Text text_;
    sf::Font font;
    font.loadFromFile(R"(C:\Windows\Fonts\arial.ttf)");

    text_.setString(this -> text);
    text_.setCharacterSize(20);
    text_.setFont(font);
    text_.setFillColor(sf::Color::White);

    sf::Vector2f textPosition = {100 + (float(texture.getSize().x) - text_.getGlobalBounds().getSize().x) / 2,
                                 100 + (float(texture.getSize().y) - text_.getGlobalBounds().getSize().y) / 2};

    text_.setPosition(textPosition);

    while(window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(box);
        window.draw(text_);
        for (int i=0 ; i < int(options.size()); i++){
            if(options[i].displayButton(window) == 1)
                return i;
        }
        window.display();
    }
    return -1;
}


Question::Question(std::string question, const std::vector<std::string>& options, const int correct, const int category_):
        Screen(std::move(question), options), correctAnswerIndex(correct), category(category_) {
}

Question::Question(const Question& other) = default;

Question& Question::operator=(const Question& other) = default;

std::ostream& operator<<(std::ostream& os, const Question& question) {
    os << "Correct answer: " << question.correctAnswerIndex << std::endl;
    return os;
}

//[[nodiscard]] int getCorrectAnswerIndex() const {return correctAnswerIndex;}
//[[nodiscard]] std::vector<std::string> getAnswerText() const {return options;}
//[[nodiscard]] std::string gettext() const {return text;}

[[nodiscard]] int Question::getCategory() const {return category;}

/*
void Question::printQuestion() const {
    std::cout << text << std::endl;

    for (long long unsigned int i = 0; i < options.size(); i++) {
        std::cout << i+1 << ". " << options[i] << std::endl;
    }
}
 */

[[nodiscard]] bool Question::checkAnswer(int userAnswer) const {
    return (userAnswer == correctAnswerIndex);
}

[[nodiscard]] bool Question::askQuestion() const {

    int userAnswer;
    std::cout << "Enter your answer: ";
    std::cin >> userAnswer;

    if (checkAnswer(userAnswer - 1)) {
        std::cout << "Correct!" << std::endl;
        return true;
    }
    else {
        std::cout << "Incorrect." << std::endl;
        return false;
    }
}
/*
Menu::Menu(std::string text, const std::vector<std::string> &button_options, std::string button_texture,
           std::string button_texture_clicked): Screen(std::move(text), button_options),
           single({200,700},"",std::move(button_texture)),
           competitive({500,700}, "", std::move(button_texture_clicked)) {

}

Menu::Menu(const Menu& other) = default;

Menu& Menu::operator=(const Menu& other) = default;
*/