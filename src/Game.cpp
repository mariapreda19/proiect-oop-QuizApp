//
// Created by maria on 4/3/2023.
//

#include "../headers/Game.h"
#include <algorithm>
#include <random>


void Game::loadQuestions(const std::string& filePath){
    std::ifstream fin(filePath);
    try {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file");
            }
            file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error opening file: " << e.what() << std::endl;
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

        Question temp_(question, answerOptions, correctAnswer, category);
        questions.emplace_back(temp_);
        answerOptions.clear();
    }
    fin.close();
}

Game::Game(const std::string& questionsFilePath, const std::vector<Player>& players_) : players(players_){
    loadQuestions(questionsFilePath);
}

Game::Game([[maybe_unused]] const Game& other) :
        questions(other.questions),
        players(other.players){
}

/*Game([[maybe_unused]] const Game&& other)  noexcept {
    questions = other.questions;
    players = other.players;
}*/

Game& Game::operator=(const Game& other) = default;

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
    while(!quit) {
        for (auto &player: players) {
            std::cout << "Player " << player.getName() << ", it's your turn!" << std::endl;

            std::vector<std::string> categorii = {"Music", "Geography", "History", "Art", "Literature", "Sports"};

            Screen screen("Categorii", categorii);


            sf::RenderWindow window;
            window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);
            window.setVerticalSyncEnabled(true);

            int categorie_aleasa = screen.displayScreen(window);

            if (categorie_aleasa != -1) {
                bool quit2 = false;
                while(!quit2) {
                    Timer time(3);
                    time.reset();

                    int number = 0;

                    std::vector<Question> category_questions;
                    for (Question &question: questions) {
                        if (categorie_aleasa == question.getCategory()) {
                            category_questions.push_back(question);
                        }
                    }

                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(category_questions.begin(), category_questions.end(), g);

                    for (Question &question: category_questions) {
                        if (time.isExpired() == 1 || number == 10) {
                            std::string message = "Player " + player.getName() + ", your final score is " +
                                                  std::to_string(std::max(player.getScore(), 0));
                            std::vector<std::string> optiuniFinal;
                            optiuniFinal.push_back("Play Again");
                            optiuniFinal.push_back("Menu");
                            optiuniFinal.push_back("Quit");
                            Screen final(message, optiuniFinal);
                            int alegereFinala = final.displayScreen(window);
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
                            number += 1;
                            int raspuns = question.displayScreen(window);
                            if (raspuns != -1) {
                                if (question.checkAnswer(raspuns))
                                    player.increaseScore(1);
                                else
                                    player.decreaseScore(0);
                            }
                        }
                    }
                }
            }
        }
    }
}
