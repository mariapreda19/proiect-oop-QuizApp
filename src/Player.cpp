//
// Created by maria on 4/3/2023.
//

#include "../headers/Player.h"

Player::Player(const Player& other): name(other.name), id(other.id), score(other.score) {
    lastId++;
}

int Player::lastId = 0;
Player::Player(std::string name_, int id_ , float score_) : name(std::move(name_)), id(id_), score(score_) {
    lastId ++;
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

float Player::getScore() const {return score;}

void Player::increaseScore(float points) {
    score += points;
}

void Player::decreaseScore(float points) {
    score -= points;
}

Player::~Player() = default;
