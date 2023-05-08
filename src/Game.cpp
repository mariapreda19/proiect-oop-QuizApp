#include "../headers/Game.h"
#include <random>


void Game::loadQuestions(const std::string& filePath){
    std::ifstream fin(filePath);
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw eroare_fisier("Failed to open file");
            }
            file.close();

    std::string question;
    std::vector<std::string> answerOptions;
    int correctAnswer;
    int category;
    while(std::getline(fin, question)){
        for(int i=0; i<4; i++){
            std::string line;
            std::getline(fin, line);
            answerOptions.emplace_back(line);
        }
        fin >> correctAnswer;
        fin >> category;
        fin.get();

        Screen * temp_  = new Question(question, answerOptions, correctAnswer, category);
        questions.emplace_back(temp_);
        answerOptions.clear();
        ///delete temp_;
    }
    fin.close();
}

Game::Game(const std::string& questionsFilePath, const std::vector<Player>& players_) : players(players_){
    loadQuestions(questionsFilePath);
}


/*Game([[maybe_unused]] const Game&& other)  noexcept {
    questions = other.questions;
    players = other.players;
}*/



std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "Questions: " << std::endl;
    for (const auto& question : game.questions) {
        os << question << std::endl;
    }
    os << "Players: " << std::endl;
    for (const auto& player : game.players) {
        os << player << std::endl;
    }
    return os;
}


void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

void Game::play(){
    bool quit = false;
    sf::RenderWindow window;
    window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);
    Player player = players[0];
    try {
        while (!quit and window.isOpen()) {
            Screen *screen = new CategoryScreen(std::string("Categorii"));

            int categorie_aleasa = screen->display(window);

            if (categorie_aleasa != -1) {
                bool quit2 = false;
                while (!quit2 and window.isOpen()) {
                    Timer clock(300);
                    clock.reset();
                    int number = 0;

                    std::vector<Question *> category_questions = shuffleQuestions(categorie_aleasa);

                    for (auto question: category_questions) {
                        if (number == 10 || clock.isExpired() == 1) {
                            std::string message;
                            if (clock.isExpired() == 1) {
                                message = "                Time is up \n Player " + player.getName() +
                                          ", your final score is " +
                                          std::to_string(std::max(player.getScore(), 0));
                            } else {
                                message =
                                        "          You have answered all the questions \n Player " + player.getName() +
                                        ", your final score is " +
                                        std::to_string(std::max(player.getScore(), 0));
                            }

                            MenuScreen final(message);
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
                        } else {
                            number += 1;
                            long long time = clock.getRemainingSeconds();

                            int raspuns = question->display(window);

                            if (raspuns != -1) {
                                std::string message;
                                if (question->checkAnswer(raspuns)) {
                                    player.increaseScore(1);
                                    message = "Player " + player.getName() + ", your score is " +
                                              std::to_string(std::max(player.getScore(), 0)) + " and you have " +
                                              std::to_string(time) + " seconds left";
                                } else {
                                    player.decreaseScore(0);
                                    message = "Player " + player.getName() + ", your score is " +
                                              std::to_string(std::max(player.getScore(), 0)) + " and you have " +
                                              std::to_string(time) + " seconds left";
                                }

                                std::vector<std::string> optiuni;
                                optiuni.emplace_back("Next Question");
                                optiuni.emplace_back("Quit");
                                MenuScreen screen1(message, optiuni);
                                auto alegere = screen1.display(window);
                                if (alegere == 1) {
                                    break;
                                }
                                if (alegere == 0) {
                                    continue;
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    catch(eroare_fereastra &er){
        std::cout << er.what() << std::endl;
    }
}




std::vector<Question *>  Game::shuffleQuestions(int category) {
    std::vector<Question *> category_questions;
    for (auto question: questions) {
        if (category== dynamic_cast<Question *>(question)->getCategory()) {
            category_questions.push_back(dynamic_cast<Question *>(question));
        }
    }


    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(category_questions.begin(), category_questions.end(), g);

    return category_questions;
}



Game::~Game() {
    delete startScreen;
    for (auto q : questions) {
        delete q;
    }
}


