#include <iostream>
#include <string>
#include <utility>
#include <vector>



class Player{
    std::string name;
    int id;
    static int lastId;
    int score;

public:

    explicit Player(std::string name_ = "", int id_ = lastId + 1, int score_ = 0) : name(std::move(name_)), id(id_), score(score_) {
        //std::cout<<"const player";
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

    /*Question(const Question&& other)  noexcept :
        questionText{other.questionText},
        answerOptions{other.answerOptions},
        correctAnswerIndex{other.correctAnswerIndex},
        level{other.level}{
    }*/

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

        int userAnswer = -1;
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

public:

    explicit Game(const std::vector<Question>& questions_ = {}, const std::vector<Player>& players_ = {}) : questions(questions_), players(players_){}

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

    void addQuestion(const Question& question) {
        questions.push_back(question);
    }

    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    void play() {
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


/**
int main(){
    Player player1;
    Timer gameTimer(0,1,1);
    std::cout << gameTimer.getSecondsLeft();
    Question qst;Question q1("What is the capital of France?", {"Paris", "London", "Rome", "Madrid"}, 0);
    q1.printQuestion();

    std::cout << std::endl;

    Question q2("Who is the author of 'To Kill a Mockingbird'?");
    q2.printQuestion();
    std::string text = q1.getQuestionText();
    std::cout << text << std::endl;

    std::vector<Question> questions;
    questions.push_back(q1);
    questions.push_back(q2);

    Player p1;
    Player p2("Bob");
    Player p3("Alice", 141, 100);

    Player p4 = p3;

    std::vector<Player> ps;
    ps.push_back(p1);
    ps.push_back(p2), ps.push_back(p3);

    p2.increaseScore(10);
    p3.decreaseScore(20);

    std::cout << p1.getName() << " has a score of " << p1.getScore() << std::endl;
    std::cout << p2.getName() << " has a score of " << p2.getScore() << std::endl;
    std::cout << p3.getName() << " has a score of " << p3.getScore() << std::endl;
    std::cout << p4.getName() << " has a score of " << p4.getScore() << std::endl;

    std::cout << Player::getLastId() << std::endl;

    Level l("easy", 1);
    std::cout << l.getName() << l.getPointsPerQuestion();
    Timer t;
    t.addTime(10);


    Game firstGame;
    Game secondGame(questions,ps);
    firstGame.addPlayer(p1);
    firstGame.addPlayer(p2);
    firstGame.addQuestion(q1);
    firstGame.play();
    return 0;
}*/

int main(){
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Christian");

    Question q1("What is the capital of France?", {"Paris", "London", "Rome", "Madrid"}, 0, 1);
    Question q2("What is the capital of UK?", {"Paris", "London", "Rome", "Madrid"}, 1, 1);
    Question q3("What is the capital of Italy?", {"Paris", "London", "Rome", "Madrid"}, 2, 1);
    Question q4("What is the capital of Spain?", {"Paris", "London", "Rome", "Madrid"}, 3, 1);
    Question q5("What is the capital of Indonesia?", {"Rome", "Jakarta", "Tokyo", "New Delhi"}, 1, 2);
    Question q6("What is the capital of Romania?", {"Rome", "Iasi", "Bucharest", "New York"}, 1, 1);

    std::vector<Question> questions;
    std::vector<Player> players;

    questions.push_back(q1);
    questions.push_back(q2);
    questions.push_back(q3);

    Game firstGame(questions, players);
    firstGame.addPlayer(p1);
    firstGame.addQuestion(q4);
    firstGame.addQuestion(q5);
    firstGame.addQuestion(q6);

    firstGame.play();
    Timer t1(0,1,1);
    t1.addTime(10);

    players.clear();
    players.push_back(p2);
    Game secondGame;
    secondGame.play();
    return 0;
}