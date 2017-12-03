#include "defs.h"

using namespace std;

Game::Game(int id_level, const char *title):level(id_level), screen(new Screen(title)){
    cout << "Création d'une instance de Game" << endl;
}

Game::~Game(){
    cout << "Destruction de l'instance Game" << endl;
    delete screen;
}
