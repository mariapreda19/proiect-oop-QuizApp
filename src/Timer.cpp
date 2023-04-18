//
// Created by maria on 4/3/2023.
//

#include "../headers/Timer.h"

Timer::Timer(int durationSeconds) : duration_{durationSeconds * 10000000000} {}

bool Timer::isExpired() const {
    std::chrono::nanoseconds elapsed = std::chrono::high_resolution_clock::now() - start_;
    return elapsed >= duration_;
}

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

