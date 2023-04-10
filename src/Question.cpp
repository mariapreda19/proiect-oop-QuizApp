//
// Created by maria on 4/3/2023.
//

#include "../headers/Question.h"


Screen::Screen(std::string text, const std::vector<std::string> &options) : text(std::move(text)){

    std::vector<Button> buttons;
    int size_ = options.size();

    for(int i=0; i < size_ ; i++){
        Button temp({200+ float(i % (size_ / 2)) * 206, 400 + float(int(i / (size_ / 2))) * 138}, options[i] ,"button.png");
        buttons.emplace_back(temp);
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
        Screen(question, options), correctAnswerIndex = correct, category = category_ {
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
