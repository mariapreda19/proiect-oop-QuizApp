//
// Created by maria on 4/3/2023.
//
#include <iostream>

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


class Player{
    std::string name;
    static int lastId;
    int id;
    float score;

public:
    explicit Player(std::string name_, int id = lastId + 1, float score_ = 0);

    Player(const Player& other);

    Player& operator=(const Player& other);

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    ///getters
    [[nodiscard]] std::string getName() const;

    //[[maybe_unused]] [[nodiscard]] int getId() const {return id;}
    //[[nodiscard]] static int getLastId() {return lastId;}
    [[nodiscard]] float getScore() const;

    void increaseScore(float points);

    void decreaseScore(float points);

    ~Player();
};



#endif //OOP_PLAYER_H
