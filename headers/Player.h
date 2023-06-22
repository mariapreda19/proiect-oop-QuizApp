//
// Created by maria on 4/3/2023.
//
#include <iostream>

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


template <typename T>
class Player{
    std::string name;
    static int lastId;
    int id;
    T score;

public:

    explicit Player(std::string name_, int id = lastId + 1, T score_ = 0):name(std::move(name_)), id(id), score(score_){lastId++;};


    friend std::ostream& operator<<(std::ostream& os, const Player<T>& player){
        os << player.name << " " << player.id << " " << " " << player.score;
        return os;
    }

    [[nodiscard]] std::string getName() const {return name;}

    [[nodiscard]] float getScore() const {return score;}

    void increaseScore(float points) {
        score += points;
    }

    void decreaseScore(float points) {
        score -= points;
    }

    ~Player() = default;
};

template <typename T>
int Player<T>::lastId = 0;



#endif //OOP_PLAYER_H
