#include "../headers/Game.h"
#include <random>

void Game::loadQuestions(const std::string& filePath, const std::string& filePathImg){
    std::ifstream fin(filePath);
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw eroare_fisier("Failed to open file");
    }
    file.close();

    std::string question;
    std::vector<std::string> answerOptions;
    int correctAnswer;
    int category;
    while(std::getline(fin, question)){
        for(int i=0; i<4; i++){
            std::string line;
            std::getline(fin, line);
            answerOptions.emplace_back(line);
        }
        fin >> correctAnswer;
        fin >> category;
        fin.get();

        Question * temp_  = new QuestionText(question, answerOptions, correctAnswer, category);
        questions.emplace_back(temp_);
        answerOptions.clear();
        ///delete temp_;
    }
    fin.close();

    std::ifstream fin2(filePathImg);

    while(std::getline(fin2, question)){
        for(int i=0; i<4; i++){
            std::string line;
            std::getline(fin2, line);
            answerOptions.emplace_back(line);
        }
        fin2 >> correctAnswer;
        fin2 >> category;
        fin2.get();

        Question * temp_  = new QuestionImage(question, answerOptions, correctAnswer, category);
        questions.emplace_back(temp_);
        answerOptions.clear();
        ///delete temp_;
    }
    fin2.close();
}

Game::Game(const std::string& questionsFilePath, const std::string& imageQuestionsFilePath, const std::vector<Player>& players_) : players(players_){
    loadQuestions(questionsFilePath, imageQuestionsFilePath);
}


/*Game([[maybe_unused]] const Game&& other)  noexcept {
    questions = other.questions;
    players = other.players;
}*/



std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "Questions: " << std::endl;
    for (const auto& question : game.questions) {
        os << question << std::endl;
    }
    os << "Players: " << std::endl;
    for (const auto& player : game.players) {
        os << player << std::endl;
    }
    return os;
}


void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

void Game::play(){
    sf::RenderWindow window;
    window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);
    Player player = players[0];

    bool quit = false;
    while (!quit and window.isOpen()) {
        Screen *screen = new CategoryScreen(std::string("Categorii"));

        int categorie_aleasa = screen->display(window);

        if (categorie_aleasa != -1) {
            bool quit2 = false;
            while (!quit2 and window.isOpen()) {
                Timer clock(30);
                Timer questionClock(5);
                clock.reset();
                int number = 0;

                std::vector<Question *> category_questions = shuffleQuestions(categorie_aleasa);

                for (auto question: category_questions) {
                    if (number == 10 || clock.isExpired() == 1) {
                        std::string message;
                        if (clock.isExpired() == 1) {
                            message = "  Time is up Player " + player.getName();
                        } else {
                            message =
                                    "You have answered all the questions Player " + player.getName();
                        }

                        ScoreScreen final(message, {"Play Again", "Back to Menu", "Quit Game"}, player.getScore());

                        int alegereFinala = final.display(window);
                        if (alegereFinala == 1) {
                            quit2 = true;
                            break;
                        }
                        if (alegereFinala == 0)
                            break;
                        if (alegereFinala == 2) {
                            quit = true;
                            quit2 = true;
                            break;
                        }
                    }
                    else {
                        number += 1;
                        long long time = clock.getRemainingSeconds();
                        long long timeQuestion = questionClock.getRemainingSeconds();


                        int raspuns = question->display(window);

                        if (raspuns != -1) {
                            std::string message;
                            if (question->checkAnswer(raspuns)) {
                                player.increaseScore(question->getScoreForQuestion(timeQuestion));
                                message = "Player " + player.getName() + ", your score is " +
                                          std::to_string(std::max(player.getScore(), 0.0f))+ " and you have " +
                                          std::to_string(time) + " seconds left";
                            }
                            else {
                                player.decreaseScore(question->getScoreForQuestion(timeQuestion));
                                message = "Player " + player.getName() + ", your score is " +
                                          std::to_string(std::max(player.getScore(), 0.0f)) + " and you have " +
                                          std::to_string(time) + " seconds left";
                            }

                            MenuScreen screen1(message);
                            auto alegere = screen1.display(window);
                            if (alegere == 1) {
                                break;
                            }
                            if (alegere == 0) {
                                questionClock.reset();
                                continue;
                            }
                        }
                    }
                }
            }

        }
        delete screen;
    }



}




std::vector<Question *>  Game::shuffleQuestions(int category) {
    std::vector<Question *> category_questions;
    for (auto question: questions) {
        if (category== question -> getCategory()) {
            category_questions.push_back(question);
        }
    }


    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(category_questions.begin(), category_questions.end(), g);

    return category_questions;
}

Game::~Game() {
    delete startScreen;
    for (auto q : questions) {
        delete q;
    }
}


