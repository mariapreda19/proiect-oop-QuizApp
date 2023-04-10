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


class Game {
private:
    Timer time;
    std::vector<Question> questions;
    std::vector<Player> players;

    void loadQuestions(const std::string& filePath);

public:

    explicit Game(const std::string& questionsFilePath, const std::vector<Player>& players_ = {});

    Game([[maybe_unused]] const Game& other);

    /*Game([[maybe_unused]] const Game&& other)  noexcept {
        questions = other.questions;
        players = other.players;
    }*/

    Game& operator=(const Game& other);

    friend std::ostream& operator<<(std::ostream& os, const Game& game);


    void addPlayer(const Player& player);

    void play();
};


#endif //OOP_GAME_H
