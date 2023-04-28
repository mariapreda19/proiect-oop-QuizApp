//
// Created by maria on 4/3/2023.
//

#include <iostream>

#ifndef OOP_TIMER_H
#define OOP_TIMER_H


#include <chrono>
#include <ctime>


class Timer {
    std::chrono::seconds duration_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
public:
    explicit Timer(int durationSeconds);
    [[nodiscard]] bool isExpired() const;
    void reset();
    [[nodiscard]] int getRemainingSeconds() const;
};


#endif //OOP_TIMER_H
