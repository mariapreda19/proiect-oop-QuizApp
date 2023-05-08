//
// Created by maria on 4/3/2023.
//

#include "../headers/Player.h"

Player::Player(const Player& other) {
    name = other.name;
    id = other.id;
    lastId++;
    score = other.score;
}

Player::Player(std::string name_, int lastId , int score_) : name(std::move(name_)), lastId(lastId), score(score_) {
    this -> id = lastId + 1;
    //std::cout<<"const player";
}


Player& Player:: operator=(const Player& other) {
    name = other.name;
    id = other.id;
    lastId++;
    score = other.score;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& player){
    os << player.name << " " << player.id << " " << " " << player.score;
    return os;
}

std::string Player::getName() const {return name;}

int Player::getScore() const {return score;}

void Player::increaseScore(int points) {
    score += points;
}

void Player::decreaseScore(int points) {
    score -= points;
}

Player::~Player() = default;
