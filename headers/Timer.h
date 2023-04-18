//
// Created by maria on 4/3/2023.
//

#include <iostream>

#ifndef OOP_TIMER_H
#define OOP_TIMER_H


#include <chrono>
#include <ctime>

class Timer {
public:
    Timer(int durationSeconds);
    bool isExpired() const;
    void reset();
private:
    std::chrono::nanoseconds duration_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};


#endif //OOP_TIMER_H
