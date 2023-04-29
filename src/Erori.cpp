//
// Created by 40773 on 23/04/2023.
//

#include "../headers/Erori.h"

eroare_fisier::eroare_fisier(const std::string& mesaj) :
    std::runtime_error("eroare fisier: " + mesaj) {}

eroare_fereastra::eroare_fereastra(const std::string& mesaj) :
    std::runtime_error("eroare fereastra: " + mesaj) {}

eroare_imagine::eroare_imagine(const std::string& mesaj) :
    eroare_fereastra("Nu a fost gasita o imagine " + mesaj) {}

eroare_font::eroare_font(const std::string& mesaj) :
    eroare_fereastra("Nu a fost gasit fontul" + mesaj) {}