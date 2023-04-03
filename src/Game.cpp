//
// Created by maria on 4/3/2023.
//

#include "../headers/Game.h"
#include <vector>
#include <fstream>


void Game::loadQuestions(const std::string& filePath){
    std::ifstream fin(filePath);
    // TODO: check if file could not be opened
    std::string question;
    std::vector<std::string> answerOptions;
    int correctAnswer;
    int level;
    while(std::getline(fin, question))
    {
        for(int i=0; i<4; i++)
        {
            std::string line;
            std::getline(fin, line);
            answerOptions.push_back(line);
        }
        fin >> correctAnswer;
        fin >> level;
        fin.get();

        questions.emplace_back(question, answerOptions, correctAnswer);
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

void Game::play() {

    for(const auto& i : questions)
        std::cout << i << "\n";

    // Play the game
    for (auto& player : players) {
        std::cout << "Player " << player.getName() << ", it's your turn!" << std::endl;

        // Display each question
        for (const auto& question : questions) {
            if(time.getSecondsLeft() == 0)
                time.finish();
            else {
                // Get answer from player
                if(question.askQuestion()) {
                    player.increaseScore(1);// se aduna sau se scad un numar de puncte egal cu gradul
                    std::cout << question.getLevel();// de dificultate al problemei
                    if(question.getLevel() >= 3){
                        time.addTime(question.getLevel());
                    }
                }
                else
                    player.decreaseScore(question.getLevel());

            }
        }

        std::cout << "Player " << player.getName() << ", your final score is " << std::max(player.getScore(),0) << std::endl;
    }
}
