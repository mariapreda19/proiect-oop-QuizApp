//
// Created by maria on 4/3/2023.
//

#include "../headers/Timer.h"

Timer::Timer(int durationSeconds) : duration_{durationSeconds}, start_{std::chrono::high_resolution_clock::now()} {}

bool Timer::isExpired() const {
    return std::chrono::high_resolution_clock::now() - start_ >= duration_;
}

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

int Timer::getRemainingSeconds() const {
    auto remainingTime = duration_ - (std::chrono::high_resolution_clock::now() - start_);
    return std::chrono::duration_cast<std::chrono::seconds>(remainingTime).count();
}
