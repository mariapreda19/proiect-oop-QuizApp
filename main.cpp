#include "headers/Player.h"
#include "headers/Timer.h"
#include "headers/Game.h"
#include "headers/Erori.h"
#include "headers/Question.h"

int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode({1000, 800}), "QuizApp", sf::Style::Default);


    std::map<std::string, std::string> filePathNames;
    filePathNames["text"] = "questions.txt";
    filePathNames["image"] = "imgQuestions.txt";
    filePathNames["multiple"] = "multipleAnswers.txt";

    StartScreen startScreen("Selectati modul de joc!");
    int choice = startScreen.display(window);

    if (choice){

        Player<int> p1("A");

        try{
            auto& firstGame = Game<int>::get_app(filePathNames, p1);

            firstGame.play(window);
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

    Player<float> p1("A");

    try{
        auto& firstGame = Game<float>::get_app(filePathNames, p1);
        firstGame.play(window);
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