//
// Created by maria on 4/3/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Player.h"
#include "Question.h"
#include "Timer.h"
#include <vector>
#include <fstream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Erori.h"


class Game {
private:
    Screen *startScreen{};
    std::vector<Question *> questions;
    std::vector<Player> players;

    void loadQuestions(const std::string& filePath, const std::string& filePathImg, const std::string& filePathMltAnswers);

public:

    explicit Game(const std::string& questionsFilePath, const std::string& imageQuestionsFilePath, const std::string& filePathMltAnswers, const std::vector<Player>& players_ = {});

    Game& operator=(const Game& other) = delete;

    Game(const Game& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);


    void addPlayer(const Player& player);

    void play();

    std::vector<Question *> shuffleQuestions(int category);


    ~Game();
};

#endif //OOP_GAME_H
