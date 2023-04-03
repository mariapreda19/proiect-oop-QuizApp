#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "headers/Player.h"
#include "headers/Timer.h"
#include "headers/Question.h"
#include "headers/Game.h"
#include "headers/Button.h"

static inline void testSFML()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    std::vector<Button> butoane;

    for(int i=0; i<6; i++)
    {
        Button temp({200+ float(i % 3) * 206, 400 +float(i / 3) * 138},"button.png");
        butoane.emplace_back(temp);
    }


    while(window.isOpen())
    {
        // Poll events
        sf::Event e{};
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i=0 ; i < int(butoane.size()); i++){
            if(butoane[i].displayButton(window) == 1)
                std::cout<<i;
        }

        window.display();
    }
}

int main(){

    testSFML();
    return 0;

    Player p1("Alice");
    Player p2("Bob");
    Player p3("Christian");

    std::vector<Player> players;


    Game firstGame("questions.txt", players);
    firstGame.addPlayer(p1);

    firstGame.play();
    Timer t1(0,1,1);
    t1.addTime(10);

    players.clear();
    players.push_back(p2);

    return 0;
}