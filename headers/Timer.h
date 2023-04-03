//
// Created by maria on 4/3/2023.
//

#include <iostream>

#ifndef OOP_TIMER_H
#define OOP_TIMER_H


class Timer{
    int start;
    int stop;
    int secondsLeft;

public:

    explicit Timer(const int start_ = 0, const int stop_ = 300, const int secondsLeft_ = 300);

    Timer(Timer const& other) noexcept;

    Timer& operator=(const Timer& other);

    friend std::ostream& operator<<(std::ostream& os, const Timer& timer);

    [[nodiscard]] int getSecondsLeft() const;

    void finish() const;

    void addTime(int moreTime);

    ~Timer();
};


#endif //OOP_TIMER_H
