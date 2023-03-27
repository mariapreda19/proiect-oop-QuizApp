#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>



class Player{
    std::string name;
    int id;
    static int lastId;
    int score;

public:

    explicit Player(std::string name_ = "", int id_ = lastId + 1, int score_ = 0) : name(std::move(name_)), id(id_), score(score_) {
        //std::cout<<"const player";
    }

    Player (const Player& other){
        name = other.name;
        id = other.id;
        lastId++;
        score = other.score;
    }

    Player& operator=(const Player& other) {
        name = other.name;
        id = other.id;
        lastId++;
        score = other.score;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player){
        os << player.name << " " << player.id << " " << " " << player.score;
        return os;
    }

    ///getters
    [[nodiscard]] std::string getName() const {return name;}

    //[[maybe_unused]] [[nodiscard]] int getId() const {return id;}
    //[[nodiscard]] static int getLastId() {return lastId;}
    [[nodiscard]] int getScore() const {return score;}

    void increaseScore(int points) {
        score += points;
    }

    void decreaseScore(int points) {
        score -= points;
    }

    ~Player() = default;
};

int Player::lastId = 0;


/*class [[maybe_unused]] Level{
    std::string name;
    int pointsPerQuestion;

public:
    Level(){
        name = "";
        pointsPerQuestion = 0;
    }
    Level(const std::string& name_, const int pointsPerQuestion_){
        name = name_;
        pointsPerQuestion = pointsPerQuestion_;
    }
    Level(Level& other){
        name = other.name;
        pointsPerQuestion = other.pointsPerQuestion;
    }
    Level(Level&& other) noexcept{
        name = other.name;
        pointsPerQuestion = other.pointsPerQuestion;
    }
    Level& operator=(const Level& other)= default;

    friend std::ostream& operator<<(std::ostream& os, const Level& lvl){
        os << lvl.name << " " << lvl.pointsPerQuestion;
        return os;
    }

    ///getters
    [[nodiscard]] std::string getName() const {return name;}
    [[nodiscard]] int getPointsPerQuestion() const {return pointsPerQuestion;}



    ~Level()= default;
};*/

class Timer{
    int start;
    int stop;
    int secondsLeft;
public:

    explicit Timer(const int start_ = 0, const int stop_ = 300, const int secondsLeft_ = 300) : start(start_) , stop(stop_), secondsLeft(secondsLeft_){
    }
    Timer(Timer const& other){
        start = other.start;
        stop = other.stop;
        secondsLeft = other.secondsLeft;
    }
    Timer(Timer&& other) noexcept{
        start = other.start;
        stop = other.stop;
        secondsLeft = other.secondsLeft;
    }
    Timer& operator=(const Timer& other)= default;

    friend std::ostream& operator<<(std::ostream& os, const Timer& timer){
        os << timer.start << " " << timer.stop << " " << timer.secondsLeft;
        return os;
    }

    //[[nodiscard]] int getStart() const {return start;}
    //[[nodiscard]] int getStop() const {return stop;}
    [[nodiscard]] int getSecondsLeft() const {return secondsLeft;}

    void finish() const{
        if(secondsLeft == 0)
            std::cout << "Time is over";
    }
    void addTime(int moreTime){
        secondsLeft += moreTime;
        stop += moreTime;
    }

    ~Timer() = default;
};


class Question {
private:
    std::string questionText;
    std::vector<std::string> answerOptions;
    int correctAnswerIndex;
    int level{};

public:
    explicit Question(std::string  question = "", const std::vector<std::string>& options = {},const int correct = -1, const int level_ = 0) :
            questionText(std::move(question)), answerOptions(options), correctAnswerIndex(correct), level(level_){
    }

    Question(const Question& other) :
        questionText{other.questionText},
        answerOptions{other.answerOptions},
        correctAnswerIndex{other.correctAnswerIndex},
        level{other.level}{
    }

    Question& operator=(const Question& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const Question& question) {
        os << "Question: " << question.questionText << std::endl;
        os << "Answer options:" << std::endl;
        for (long long unsigned int i = 0; i < question.answerOptions.size(); i++) {
            os << i+1 << ". " << question.answerOptions[i] << std::endl;
        }
        os << "Correct answer: " << question.answerOptions[question.correctAnswerIndex] << std::endl;
        return os;
    }

    //[[nodiscard]] int getCorrectAnswerIndex() const {return correctAnswerIndex;}
    //[[nodiscard]] std::vector<std::string> getAnswerText() const {return answerOptions;}
    //[[nodiscard]] std::string getQuestionText() const {return questionText;}
    [[nodiscard]] int getLevel() const {return level;}

    void printQuestion() const {
        std::cout << questionText << std::endl;

        for (long long unsigned int i = 0; i < answerOptions.size(); i++) {
            std::cout << i+1 << ". " << answerOptions[i] << std::endl;
        }
    }
    [[nodiscard]] bool checkAnswer(int userAnswer) const {
        return (userAnswer == correctAnswerIndex);
    }

    [[nodiscard]] bool askQuestion() const {
        printQuestion();

        int userAnswer;
        std::cout << "Enter your answer: ";
        std::cin >> userAnswer;

        if (checkAnswer(userAnswer - 1)) {
            std::cout << "Correct!" << std::endl;

            return true;
        } else {
            std::cout << "Incorrect." << std::endl;
            return false;
        }
    }
};

class Game {
private:
    Timer time;
    std::vector<Question> questions;
    std::vector<Player> players;

    void loadQuestions(const std::string& filePath){
        std::ifstream fin(filePath);
        // TODO: check if file could not be opened
        std::string question;
        std::vector<std::string> answerOptions;
        int correctAnswer;
        while(std::getline(fin, question))
        {
            for(int i=0; i<4; i++)
            {
                std::string line;
                std::getline(fin, line);
                answerOptions.push_back(line);
            }
            fin >> correctAnswer; fin.get();

            questions.emplace_back(question, answerOptions, correctAnswer);
            answerOptions.clear();
        }
        fin.close();
    }

public:

    explicit Game(const std::string& questionsFilePath, const std::vector<Player>& players_ = {}) : players(players_){
        loadQuestions(questionsFilePath);
    }

    Game([[maybe_unused]] const Game& other) :
        questions{other.questions},
        players{other.players}{
    }

    /*Game([[maybe_unused]] const Game&& other)  noexcept {
        questions = other.questions;
        players = other.players;
    }*/

    Game& operator=(const Game& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
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


    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    void play() {

        for(const auto& i : questions)
            std::cout << i << "\n";

        // Play the game
        for (auto& player : players) {
            std::cout << "Player " << player.getName() << ", it's your turn!" << std::endl;

            // Display each question
            for (const auto& question : questions) {
                if(time.getSecondsLeft() == 0)
                    time.finish();
                else {
                    // Get answer from player
                    if(question.askQuestion()) {
                        player.increaseScore(question.getLevel()); // se aduna sau se scad un numar de puncte egal cu gradul
                                                                         // de dificultate al problemei
                        if(question.getLevel() >= 3){
                            time.addTime(question.getLevel());
                        }
                    }
                    else
                        player.decreaseScore(question.getLevel());

                }
            }

            std::cout << "Player " << player.getName() << ", your final score is " << std::max(player.getScore(),0) << std::endl;
        }
    }
};

int main(){
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Christian");

    std::vector<Player> players;


    Game firstGame("questions.txt", players);
    firstGame.addPlayer(p1);

    firstGame.play();
    Timer t1(0,1,1);
    t1.addTime(10);

    players.clear();
    players.push_back(p2);
    return 0;
}