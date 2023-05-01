#include "../headers/Game.h"
#include <random>


void Game::loadQuestions(const std::string& filePath){
    std::ifstream fin(filePath);
    try {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw eroare_fisier("Failed to open file");
            }
            file.close();
    } catch (const std::exception& e) {
        std::cerr << filePath << e.what() << std::endl;
    }
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

        Screen * temp_  = new Question(question, answerOptions, correctAnswer, category);
        questions.emplace_back(temp_);
        answerOptions.clear();
        ///delete temp_;
    }
    fin.close();
}

Game::Game(const std::string& questionsFilePath, const std::vector<Player>& players_) : players(players_){
    loadQuestions(questionsFilePath);
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
    bool quit = false;
    sf::RenderWindow window;
    window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);

    while(!quit and window.isOpen()) {
        for (auto &player: players) {

            Screen * screen = new CategoryScreen(std::string("Categorii"));

            int categorie_aleasa = screen->display(window);

            if (categorie_aleasa != -1) {
                bool quit2 = false;
                while(!quit2 and window.isOpen()) {
                    Timer clock(300);
                    clock.reset();
                    int number = 0;
                    std::vector<Question *> category_questions;
                    for (auto question: questions) {
                        if (categorie_aleasa == dynamic_cast<Question *>(question)->getCategory()) {
                            category_questions.push_back(dynamic_cast<Question *>(question));
                        }
                    }

                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(category_questions.begin(), category_questions.end(), g);

                    for (auto question: category_questions) {
                        if (number == 10 || clock.isExpired() == 1) {
                            if(clock.isExpired() == 1) {
                                std::string message = "                Time is up \n Player " + player.getName() +
                                                      ", your final score is " +
                                                      std::to_string(std::max(player.getScore(), 0));

                                MenuScreen final(message);
                                int alegereFinala = final.display(window);
                                if(alegereFinala == 1) {
                                    quit2 = true;
                                    break;
                                }
                                if(alegereFinala == 0)
                                    break;
                                if(alegereFinala == 2){
                                    quit = true;
                                    quit2 = true;
                                    break;
                                }

                            }
                            else {
                                std::string message =
                                        "          You have answered all the questions \n Player " + player.getName() +
                                        ", your final score is " +
                                        std::to_string(std::max(player.getScore(), 0));
                                std::vector<std::string> optiuniFinal;
                                optiuniFinal.push_back("Play Again");
                                optiuniFinal.push_back("Menu");
                                optiuniFinal.push_back("Quit");
                                MenuScreen final(message, optiuniFinal);
                                int alegereFinala = final.display(window);
                                if(alegereFinala == 1) {
                                    quit2 = true;
                                    break;
                                }
                                if(alegereFinala == 0)
                                    break;
                                if(alegereFinala == 2){
                                    quit = true;
                                    quit2 = true;
                                    break;
                                }
                            }
                        }
                        else {
                            number += 1;
                            long long time = clock.getRemainingSeconds();


                            int raspuns = question -> display(window);
                            if (raspuns != -1) {
                                if (question -> checkAnswer(raspuns)) {
                                    player.increaseScore(1);
                                    std::string message = "Player " + player.getName() + ", your score is " +
                                                          std::to_string(std::max(player.getScore(), 0)) + " and you have " +
                                                          std::to_string(time) + " seconds left";
                                    std::vector<std::string> optiuni;
                                    optiuni.push_back("Next Question");
                                    optiuni.push_back("Quit");
                                    MenuScreen screen1(message, optiuni);
                                    int alegere = screen1.display(window);
                                    if (alegere == 1) {
                                        break;
                                    }
                                    if (alegere == 0) {
                                        continue;
                                    }

                                }
                                else {
                                    player.decreaseScore(0);
                                    std::string message = "Player " + player.getName() + ", your score is " +
                                                          std::to_string(std::max(player.getScore(), 0)) + " and you have " +
                                                          std::to_string(time) + " seconds left";
                                    std::vector<std::string> optiuni;
                                    optiuni.push_back("Next Question");
                                    optiuni.push_back("Quit");
                                    MenuScreen screen1(message, optiuni);
                                    int alegere = screen1.display(window);
                                    if (alegere == 1) {
                                        break;
                                    }
                                    if (alegere == 0) {
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
Game::~Game() {
    delete startScreen;
    for (auto q : questions) {
        delete q;
    }
}


