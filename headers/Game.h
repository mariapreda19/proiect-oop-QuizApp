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
    std::map<std::string, std::string> filePathNames;
    Player currentPlayer;

    explicit Game(const std::map<std::string, std::string> &filePathNames_ , const Player& currentPlayer_);

    void loadQuestions();

public:

    static Game& get_app(const std::map<std::string, std::string>& filePathNames, const Player& currentPlayer);

    Game& operator=(const Game& other) = delete;

    Game(const Game& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);

    void play();

    std::vector<Question *> shuffleQuestions(int category);


    ~Game();
};

#endif //OOP_GAME_H
