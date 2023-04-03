//
// Created by maria on 4/3/2023.
//

#include "../headers/Timer.h"

Timer::Timer(const int start_, const int stop_, const int secondsLeft_) : start(start_) , stop(stop_), secondsLeft(secondsLeft_){}

Timer::Timer(Timer const& other) noexcept: start(other.start), stop(other.stop), secondsLeft(other.secondsLeft){}

Timer& Timer:: operator=(const Timer& other)= default;

std::ostream& operator<<(std::ostream& os, const Timer& timer){
    os << timer.start << " " << timer.stop << " " << timer.secondsLeft;
    return os;
}

[[nodiscard]] int Timer::getSecondsLeft() const {return secondsLeft;}

void Timer::finish() const{
    if(secondsLeft == 0)
        std::cout << "Time is over";
}
void Timer::addTime(int moreTime){
    secondsLeft += moreTime;
    stop += moreTime;
}

Timer::~Timer() = default;