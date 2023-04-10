//
// Created by maria on 4/3/2023.
//

#include "../headers/Game.h"

void Game::loadQuestions(const std::string& filePath){
    std::ifstream fin(filePath);
    // TODO: check if file could not be opened
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

        questions.emplace_back(question, answerOptions, correctAnswer, category);
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

    for (auto& player : players) {
        std::cout << "Player " << player.getName() << ", it's your turn!" << std::endl;

        std::vector<Button> butoane;
        std::vector<std::string> categorii = {"Music", "Geography", "History", "Art", "Literature", "Sports"};

        for (int i = 0; i < 6; i++) {
            Button temp({200 + float(i % 3) * 206, 400 + float(int(i / 3)) * 138}, categorii[i], "button.png");
            butoane.emplace_back(temp);
        }

        Screen screen("Categorii", butoane);


        sf::RenderWindow window;
        window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);
        window.setVerticalSyncEnabled(true);

        int categorie_aleasa = screen.displayScreen(window);

        if (categorie_aleasa) {
            for (Question &question: questions)
                if (categorie_aleasa == question.getCategory()) {
                    if (time.getSecondsLeft() == 0)
                        time.finish();
                    else {
                        int raspuns = question.displayScreen(window);
                        if (raspuns != -1) {
                            if (question.checkAnswer(raspuns))
                                player.increaseScore(1);
                            else
                                player.decreaseScore(1);
                        }
                    }
                }
        }

        std::cout << "Player " << player.getName() << ", your final score is " << std::max(player.getScore(),0) << std::endl;
    }
}
