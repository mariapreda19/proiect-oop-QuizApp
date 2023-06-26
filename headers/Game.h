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
#include <random>
#include <memory>


template <typename T>
class Game {
private:
    Screen *startScreen{};
    std::vector<Question *> questions;
    std::map<std::string, std::string> filePathNames;
    Player<T> currentPlayer;

    void loadQuestions(){
        /*QuestionImage::loadQuestions(questions, filePathNames);
        QuestionText::loadQuestions(questions, filePathNames);
        MultipleAnswers::loadQuestions(questions, filePathNames);*/

        AbstractQuestionFactory * questionFactory = new QuestionTextFactory();

        //questions.insert(questions.end(), questionFactory->createQuestion(filePathNames).begin(), questionFactory->createQuestion(filePathNames).end());
        for (auto& question : questionFactory->createQuestion(filePathNames)) {
            questions.push_back(question);
        }


        questionFactory = new QuestionImageFactory();

        //questions.insert(questions.end(), questionFactory->createQuestion(filePathNames).begin(), questionFactory->createQuestion(filePathNames).end());

        for (auto& question : questionFactory->createQuestion(filePathNames)) {
            questions.push_back(question);
        }


        questionFactory = new MultipleAnswersFactory();

        //questions.insert(questions.end(), questionFactory->createQuestion(filePathNames).begin(), questionFactory->createQuestion(filePathNames).end());

        for (auto& question : questionFactory->createQuestion(filePathNames)) {
            questions.push_back(question);
        }

        delete questionFactory;
    }

    Game (const std::map<std::string, std::string> &filePathNames_,const Player<T>& currentPlayer_) :  filePathNames(filePathNames_), currentPlayer(currentPlayer_){
        loadQuestions();
    }

public:

//    Game<T>& operator=(const Game& other) = delete;
//
//    Game<T>(const Game& other) = delete;

    void play(sf::RenderWindow &window){

        bool quit = false;
        window.setFramerateLimit(10);

        window.setVerticalSyncEnabled(true);
        while (!quit and window.isOpen()) {
            Screen *screen = new CategoryScreen(std::string("Categorii"));

            int categorie_aleasa = screen->display(window);

            if (categorie_aleasa != -1) {
                bool quit2 = false;
                while (!quit2 and window.isOpen()) {

                    Timer clock(30);
                    Timer questionClock(5);
                    clock.reset();
                    int number = 0;

                    std::vector<Question *> category_questions = shuffleQuestions(categorie_aleasa);

                    for (auto question: category_questions) {
                        if (number == 10 || clock.isExpired() == 1) {
                            std::string message;
                            if (clock.isExpired() == 1) {
                                message = "  Time is up Player " + currentPlayer.getName();
                            } else {
                                message =
                                        "You have answered all the questions Player " + currentPlayer.getName();
                            }

                            ScoreScreen final(message, {"Play Again", "Back to Menu", "Quit Game"}, currentPlayer.getScore());

                            int alegereFinala = final.display(window);
                            if (alegereFinala == 1) {
                                quit2 = true;
                                break;
                            }
                            if (alegereFinala == 0)
                                break;
                            if (alegereFinala == 2) {
                                quit = true;
                                quit2 = true;
                                break;
                            }
                        }
                        else {
                            number += 1;
                            long long time = clock.getRemainingSeconds();
                            long long timeQuestion = questionClock.getRemainingSeconds();


                            int raspuns = question->display(window);

                            if (raspuns != -1) {
                                std::string message;
                                if (question->checkAnswer(raspuns)) {
                                    currentPlayer.increaseScore(question->getScoreForQuestion(timeQuestion));
                                    message = "Player " +  currentPlayer.getName() + ", your score is " +
                                              std::to_string(std::max(currentPlayer.getScore(), 0.0f))+ " and you have " +
                                              std::to_string(time) + " seconds left";
                                }
                                else {
                                    currentPlayer.decreaseScore(question->getScoreForQuestion(timeQuestion));
                                    message = "Player " + currentPlayer.getName() + ", your score is " +
                                              std::to_string(std::max(currentPlayer.getScore(), 0.0f)) + " and you have " +
                                              std::to_string(time) + " seconds left";
                                }

                                MenuScreen screen1(message);
                                auto alegere = screen1.display(window);
                                if (alegere == 1) {
                                    break;
                                }
                                if (alegere == 0) {
                                    questionClock.reset();
                                    continue;
                                }
                            }
                        }
                    }
                }

            }
            delete screen;
        }
    }

    std::vector<Question *> shuffleQuestions(int category) {
        std::vector<Question *> category_questions;
        for (auto question: questions) {
            if (category== question -> getCategory()) {
                category_questions.push_back(question);
            }
        }


        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(category_questions.begin(), category_questions.end(), g);

        return category_questions;
    }

    ~Game() {
        delete startScreen;
        for (auto q : questions) {
            delete q;
        }
    }

    static Game& get_app(const std::map<std::string, std::string>& filePathNames_, const Player<T>& players) {
        static Game app(filePathNames_, players);
        return app;
    }
};

#endif //OOP_GAME_H
