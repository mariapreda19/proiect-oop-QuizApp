//
// Created by 40773 on 23/04/2023.
//

#ifndef OOP_ERORI_H
#define OOP_ERORI_H
#include <stdexcept>
#include <string>

class eroare_joc : public std::runtime_error {
public:
    explicit eroare_joc(const std::string& mesaj);
};

class eroare_fisier : public eroare_joc {
public:
    explicit eroare_fisier(const std::string& mesaj);
};

class eroare_fereastra : public eroare_joc {
public:
    explicit eroare_fereastra(const std::string& mesaj);
};

class eroare_imagine : public eroare_fereastra {
public:
    explicit eroare_imagine(const std::string& mesaj);
};

class eroare_font : public eroare_fereastra {
public:
    explicit eroare_font(const std::string& mesaj);
};

#endif //OOP_ERORI_H
