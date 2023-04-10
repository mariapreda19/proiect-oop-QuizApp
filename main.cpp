#include <vector>

#include "headers/Player.h"
#include "headers/Timer.h"
#include "headers/Question.h"
#include "headers/Button.h"
#include "headers/Game.h"

int main(){

    Player p1("A");
    std::vector<Player> players;

    Game firstGame("questions.txt", players);
    firstGame.addPlayer(p1);

    firstGame.play();


    return 0;
}