//
// Created by maria on 23/04/2023.
//

#include "../headers/Erori.h"
eroare_joc::eroare_joc(const std::string& mesaj) :
    std::runtime_error(std::string("eroare joc: ") + mesaj) {}

eroare_fisier::eroare_fisier(const std::string& mesaj) :
    eroare_joc(std::string("eroare fisier: ") + mesaj) {}

eroare_fereastra::eroare_fereastra(const std::string& mesaj) :
    eroare_joc(std::string("eroare fereastra: ") + mesaj) {}

eroare_imagine::eroare_imagine(const std::string& mesaj) :
    eroare_fereastra(std::string("Nu a fost gasita o imagine ") + mesaj) {}

eroare_font::eroare_font(const std::string& mesaj) :
    eroare_fereastra(std::string("Nu a fost gasit fontul") + mesaj) {}