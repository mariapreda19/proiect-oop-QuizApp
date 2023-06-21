#include "headers/Player.h"
#include "headers/Timer.h"
#include "headers/Game.h"
#include "headers/Erori.h"

int main(){

    auto& p1 = Player::get_player("A");

    std::map<std::string, std::string> filePathNames;
    filePathNames["text"] = "questions.txt";
    filePathNames["image"] = "imgQuestions.txt";
    filePathNames["multiple"] = "multipleAnswers.txt";

    try{
        auto& firstGame = Game::get_app(filePathNames, p1);

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


    return 0;
}