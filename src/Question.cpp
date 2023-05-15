//
// Created by maria on 4/3/2023.
//

#include <utility>

#include "../headers/Question.h"


Screen::Screen(std::string text, const std::vector<std::string> &button_options) : text(std::move(text)){

    unsigned long long int size_ = button_options.size();

    //float space_left = float(1000 - (196 * int(size_ / 2) + 20 * (int(size_ / 2) - 1))) / 2;


    for(unsigned long long int i=0; i < size_ ; i++){
        Button temp(button_options[i] ,"button.png");
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



int Screen::display (sf::RenderWindow &window){

    sf::Texture background;
    background.loadFromFile("background.jpg");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Sprite box;
    sf::Texture texture;
    texture.loadFromFile("button2.png");
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
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);


        for (int i=0 ; i < int(options.size()); i++){
            if(options[i].displayButton(window,{0,0}) == 1)
                return i;
        }

        window.display();
    }
    return -1;
}

std::basic_string<char> Screen::getText() const {
    return text;
}
std::vector<Button> Screen::getOptions() const {
    return options;
}

void Screen::setText(const std::string &text_) {
    Screen::text = text_;
}


Question::Question(std::string question, const std::vector<std::string>& options, const int correct, const int category_, const float score_):
        Screen(std::move(question), options), correctAnswerIndex(correct), category(category_), score(score_){
}



//Question& Question::operator=(const Question& other) = default;

std::ostream& operator<<(std::ostream& os, const Question& question) {
    os << "Correct answer: " << question.correctAnswerIndex << std::endl;
    return os;
}
//[[nodiscard]] int getCorrectAnswerIndex() const {return correctAnswerIndex;}
//[[nodiscard]] std::vector<std::string> getAnswerText() const {return options;}
//[[nodiscard]] std::string gettext() const {return text;}

[[nodiscard]] int Question::getCategory() const {return category;}

[[nodiscard]] bool Question::checkAnswer(int userAnswer) const {
    return (userAnswer == correctAnswerIndex);
}


int Question::display(sf::RenderWindow &window) {
    sf::Texture background;
    if(!background.loadFromFile("background.jpg"))
        throw eroare_imagine("Imaginea nu a putut fi incarcata");


    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Texture texture;

    if(!texture.loadFromFile("button2.png"))
        throw eroare_imagine("Imaginea nu a putut fi incarcata");

    sf::Sprite box;
    box.setTexture(texture);
    box.setPosition(100, 100);


    sf::Font font;

    if(!font.loadFromFile("arial.ttf"))
        throw eroare_font("Fontul nu a putut fi incarcat");


    sf::Text text_;
    text_.setString(this -> getText());
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
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);



        for (int i=0 ; i < 4; i++){
            if(getOptions()[i].displayButton(window, {294+float(i%2)*216, 400 + float(int(i/2))*138}) == 1)
                return i;
        }
        window.display();
    }
    return -1;
}

MenuScreen::MenuScreen(std::string text, const std::vector<std::string> &button_options) : Screen(std::move(text), button_options) {}

//MenuScreen::MenuScreen(const MenuScreen &other) = default;

//MenuScreen &MenuScreen::operator=(const MenuScreen &other) = default;

int MenuScreen::display(sf::RenderWindow &window) {
    sf::Texture background;

    background.loadFromFile("background.jpg");


    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Sprite box;
    sf::Texture texture;

    texture.loadFromFile("button2.png");


    box.setTexture(texture);
    box.setPosition(100, 100);

    sf::Text text_;
    sf::Font font;

    font.loadFromFile("arial.ttf");


    text_.setString(getText());
    text_.setCharacterSize(20);
    text_.setFont(font);
    text_.setFillColor(sf::Color::White);

    sf::Vector2f textPosition = {100 + (float(texture.getSize().x) - text_.getGlobalBounds().getSize().x) / 2,
                                 100 + (float(texture.getSize().y) - text_.getGlobalBounds().getSize().y) / 2};

    text_.setPosition(textPosition);

    while(window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);
        for (int i=0 ; i < 2; i++){
            if(getOptions()[i].displayButton(window, { 402 + float(int(i/2)) * 216, 400 + float(int(i / (3 / 2))) * 138}) == 1)
                return i;
        }


        window.display();
    }
    return -1;
}



CategoryScreen::CategoryScreen(std::string text, const std::vector<std::string> &button_options) : Screen(std::move(text), button_options){}
//CategoryScreen::CategoryScreen(const CategoryScreen &other) = default;
//CategoryScreen &CategoryScreen::operator=(const CategoryScreen &other) = default;
int CategoryScreen::display(sf::RenderWindow &window) {
    sf::Texture background;

    background.loadFromFile("background.jpg");


    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Sprite box;
    sf::Texture texture;

    texture.loadFromFile("button2.png");

    box.setTexture(texture);
    box.setPosition(100, 100);

    sf::Text text_;
    sf::Font font;

    font.loadFromFile("arial.ttf");


    text_.setString(getText());
    text_.setCharacterSize(20);
    text_.setFont(font);
    text_.setFillColor(sf::Color::White);

    sf::Vector2f textPosition = {100 + (float(texture.getSize().x) - text_.getGlobalBounds().getSize().x) / 2,
                                 100 + (float(texture.getSize().y) - text_.getGlobalBounds().getSize().y) / 2};

    text_.setPosition(textPosition);

    while(window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);


        for (int i=0 ; i < 6; i++){
            if(getOptions()[i].displayButton(window, {200 + float(i%3)*216, 400+float(int(i/3))*138}) == 1)
                return i;
        }

        window.display();
    }
    return -1;

}


ScoreScreen::ScoreScreen(const std::string& text, const std::vector<std::string> &button_options, float score_) :
        Screen(text, button_options), score(score_) {}


int ScoreScreen::display(sf::RenderWindow &window) {
    sf::Texture background;

    background.loadFromFile("background.jpg");


    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Sprite box;
    sf::Texture texture;

    texture.loadFromFile("button2.png");

    box.setTexture(texture);
    box.setPosition(100, 100);

    sf::Text text_;
    sf::Font font;

    font.loadFromFile("arial.ttf");

    setText(getText() + std::string("\nYour score is: ") + std::to_string(score));

    text_.setString(getText());
    text_.setCharacterSize(20);
    text_.setFont(font);
    text_.setFillColor(sf::Color::White);

    sf::Vector2f textPosition = {100 + (float(texture.getSize().x) - text_.getGlobalBounds().getSize().x) / 2,
                                 100 + (float(texture.getSize().y) - text_.getGlobalBounds().getSize().y) / 2};

    text_.setPosition(textPosition);

    while(window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);


        for (int i=0 ; i <= 2; i++){
            if(getOptions()[i].displayButton(window, {200 + float(i%3)*216, 400+float(int(i/3))*138}) == 1)
                return i;
        }

        window.display();
    }
    return -1;
}


int QuestionImage::display(sf::RenderWindow &window) {
    sf::Texture background;
    if(!background.loadFromFile("background.jpg"))
        throw eroare_imagine("Imaginea nu a putut fi incarcata");

    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Texture texture;


    if(texture.loadFromFile(this -> image_path))
        throw eroare_imagine("Imaginea nu a putut fi incarcata");


    sf::Sprite box;
    box.setTexture(texture);
    box.setPosition((float(1000) - float(texture.getSize().x))/2, 50);


    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        throw eroare_font("Fontul nu a putut fi incarcat");


    sf::Text text_;
    text_.setString(this -> getText());
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
        window.draw(background_sprite);
        window.draw(box);
        window.draw(text_);



        for (int i=0 ; i < 4; i++){
            if(getOptions()[i].displayButton(window, {294+float(i%2)*216, float(100 + texture.getSize().y) + float(int(i/2))*138}) == 1)
                return i;
        }
        window.display();
    }
    return -1;
}

float QuestionImage::getScoreForQuestion(long long time) {
    return score * 1.0f * float(5-time);
}

float QuestionText::getScoreForQuestion(long long time) {
    return score * 1.0f - (float(time)) / 5;
}
