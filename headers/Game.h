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
#include "SFML/Graphics.hpp"
#include "Erori.h"


class Game {
private:
    Screen *startScreen{};
    std::vector<Screen *> questions;
    std::vector<Player> players;

    void loadQuestions(const std::string& filePath);

public:

    explicit Game(const std::string& questionsFilePath, const std::vector<Player>& players_ = {});


    /*Game([[maybe_unused]] const Game&& other)  noexcept {
        questions = other.questions;
        players = other.players;
    }*/

    friend std::ostream& operator<<(std::ostream& os, const Game& game);


    void addPlayer(const Player& player);

    void play();

    virtual ~Game();
};

#endif //OOP_GAME_H
