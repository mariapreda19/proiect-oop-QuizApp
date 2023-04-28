//
// Created by 40773 on 23/04/2023.
//

#ifndef OOP_ERORI_H
#define OOP_ERORI_H
#include <stdexcept>

class eroare_fisier : public std::runtime_error {
public:
    explicit eroare_fisier(const std::string& mesaj);
};

class eroare_fereastra : public std::runtime_error {
public:
    explicit eroare_fereastra(const std::string& mesaj);
};

#endif //OOP_ERORI_H
