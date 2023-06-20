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
    std::vector<Player> players;

    explicit Game(const std::map<std::string, std::string> &filePathNames_ , const std::vector<Player>& players_ = {});

    void loadQuestions();

public:

    static Game& get_app(const std::map<std::string, std::string> filePathNames, std::vector<Player> players) {
        static Game app(filePathNames, players);
        return app;
    }

    Game& operator=(const Game& other) = delete;

    Game(const Game& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);


    void addPlayer(const Player& player);

    void play();

    std::vector<Question *> shuffleQuestions(int category);


    ~Game();
};

#endif //OOP_GAME_H
