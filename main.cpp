#include <iostream>
#include <string>
//#include <vector>
#include <utility>
//#include <random>
#include <algorithm>

class Player{
    std::string name;
    int id;
    static int lastId;
    int bestScore;

public:
    Player(){
        name = "";
        id = lastId + 1;
        bestScore = 0;
    }
    Player(const std::string& name_, const int id_, const int lastId_, const int bestScore_){
        name = name_;
        id = id_;
        lastId = lastId_;
        bestScore = bestScore_;
    }
    Player(Player& other){
        name = other.name;
        id = other.id;
        lastId = other.lastId;
        bestScore = other.bestScore;
    }
    Player(Player&& other){
        name = std::move(other.name);
        id = std::move(other.id);
        lastId = std::move(other.lastId);
        bestScore = std::move(other.bestScore);
    }
    Player& operator=(const Player& other) {
        name = other.name;
        id = other.id;
        lastId = other.lastId;
        bestScore = other.bestScore;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player){
        os << player.name << " " << player.id << " " << player.lastId << " " << player.bestScore;
        return os;
    }

    ///getters
    std::string getName() const {return name;}
    int getId() const {return id;}
    int getLastId() const {return lastId;}
    int getBestScore() const {return bestScore;}

    void newBestScore(int newScore){
        if(bestScore < newScore)
            bestScore = newScore;
    }
    ~Player() {}
};

int Player::lastId = 0;

class Level{
    std::string name;
    int pointsPerQuestion;

public:
    Level(){
        name = "";
        pointsPerQuestion = 0;
    }
    Level(const std::string name_, const int pointsPerQuestion_){
        name = name_;
        pointsPerQuestion = pointsPerQuestion_;
    }
    Level(Level& other){
        name = other.name;
        pointsPerQuestion = other.pointsPerQuestion;
    }
    Level(Level&& other){
        name = std::move(other.name);
        pointsPerQuestion = std::move(other.pointsPerQuestion);
    }
    Level& operator=(const Level& other){
        name = other.name;
        pointsPerQuestion = other.pointsPerQuestion;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Level& lvl){
        os << lvl.name << " " << lvl.pointsPerQuestion;
        return os;
    }

    ///getters
    std::string getName() const {return name;}
    int getPointsPerQuestion() const {return pointsPerQuestion;}



    ~Level(){}
};

class Timer{
    int start;
    int stop;
    int secondsLeft;
public:
    Timer(){
        start = 0;
        stop = 0;
        secondsLeft = 300;
    }
    Timer(const int start_, const int stop_, const int secondsLeft_){
        start = start_;
        stop = stop_;
        secondsLeft = secondsLeft_;
    }
    Timer(Timer& other){
        start = other.start;
        stop = other.stop;
        secondsLeft = other.secondsLeft;
    }
    Timer(Timer&& other){
        start = std::move(other.start);
        stop = std::move(other.stop);
        secondsLeft = std::move(other.secondsLeft);
    }
    Timer& operator=(const Timer& other){
        start = other.start;
        stop = other.stop;
        secondsLeft = other.secondsLeft;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Timer& timer){
        os << timer.start << " " << timer.stop << " " << timer.secondsLeft;
        return os;
    }

    ///getters
    int getStart() const {return start;}
    int getStop() const {return stop;}
    int getSecondsLeft() const {return secondsLeft;}

    void finish(){
        if(secondsLeft == 0)
            std::cout << "Time is over";
    }
    void addTime(int moreTime){
        secondsLeft += moreTime;
        stop += moreTime;
    }

    ~Timer() {}
};
class Question{
    std::string text;
    std::string answer1;
    std::string answer2;
    std::string answer3;
    std::string answer4;
    int correctAnswer;
    int questionScore;
public:
    Question(){
        text = "";
        answer1 = "";
        answer2 = "";
        answer3 = "";
        answer4 = "";
        correctAnswer = 1;
        questionScore = 0;
    }
    Question(const std::string text_, const std::string answer1_, const std::string answer2_, const std::string answer3_,
             const std::string answer4_, const int correctAnswer_, const int questionScore_){
        text = text_;
        answer1 = answer1_;
        answer2 = answer2_;
        answer3 = answer3_;
        answer4 = answer4_;
        correctAnswer = correctAnswer_;
        questionScore = questionScore_;
    }
    Question(Question& other){
        text = other.text;
        answer1 = other.answer1;
        answer2 = other.answer2;
        answer3 = other.answer3;
        answer4 = other.answer4;
        correctAnswer = other.correctAnswer;
        questionScore = other.questionScore;
    }
    Question(Question&& other){
        text = std::move(other.text);
        answer1 = std::move(other.answer1);
        answer2 = std::move(other.answer2);
        answer3 = std::move(other.answer3);
        answer4 = std::move(other.answer4);
        correctAnswer = std::move(other.correctAnswer);
        questionScore = std::move(other.questionScore);
    }
    Question& operator=(const Question& other){
        text = other.text;
        answer1 = other.answer1;
        answer2 = other.answer2;
        answer3 = other.answer3;
        answer4 = other.answer4;
        correctAnswer = other.correctAnswer;
        questionScore = other.questionScore;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Question& question){
        os << question.text << " " <<  question.answer1 << " " << question.answer2 << " " << question.answer3;
        os << question.answer4 << " " << question.correctAnswer << " " << question.questionScore;
        return os;
    }

    ///getters
    std::string getText() const { return text; }
    std::string getAnswer1() const { return answer1; }
    std::string getAnswer2() const { return answer2; }
    std::string getAnswer3() const { return answer3; }
    std::string getAnswer4() const { return answer4; }
    int getCorrectAnswer() const { return correctAnswer; }
    int getQuestionScore() const { return questionScore; }



    ~Question(){}
};

int main(){
    Player player1;
    Timer gameTimer;
    Question qst;
    Level lvl;
    return 0;
}