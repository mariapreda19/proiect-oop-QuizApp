#include <vector>

#include "headers/Player.h"
#include "headers/Timer.h"
#include "headers/Game.h"
#include "headers/Erori.h"

int main(){

    Player p1("A");
    std::vector<Player> players;

    std::map<std::string, std::string> filePathNames;
    filePathNames["text"] = "questions.txt";
    filePathNames["image"] = "imgQuestions.txt";
    filePathNames["multiple"] = "multipleAnswers.txt";

    try{
        Game firstGame(filePathNames,players);
        firstGame.addPlayer(p1);

        firstGame.play();
    }
    catch (const eroare_fisier& er) {
        std::cerr << er.what() << std::endl;
    }
    catch(const eroare_fereastra& er){
        std::cerr << er.what() << std::endl;
    }
    catch(const eroare_joc& er){
        std::cerr << er.what() << std::endl;
    }



    /*TODO
      -> nu mai am niciun atribut de tip static sau functie
      -> ? mai e nevoie de suprascrierea cc/op=
      */
    return 0;
}