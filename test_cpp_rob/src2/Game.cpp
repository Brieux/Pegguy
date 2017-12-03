#include "defs.h"

using namespace std;

Game::Game(int id_level, const char *title, int wmap, int hmap):level(id_level), screen(new Screen(title)), wmap(wmap), hmap(hmap){
    cout << "Création d'une instance de Game" << endl;
}

Game::~Game(){
    cout << "Destruction de l'instance Game" << endl;
    delete screen;
}

void Game::Calcul_Dep(int &dep_x, int &dep_y){   //Ne marche pas tant que perso n'est pas créé
    if (perso.Get_x > WINDOW_W/2){
        if (perso.Get_x > wmap * 32 - WINDOW_W/2){
            dep_x = wmap * 32 - WINDOW_W;
        } else {
            dep_x = perso.Get_x - WINDOW_W/2;
        }
    } else {
        dep_x = 0;
    }

    if (perso.Get_y > WINDOW_H/2){
        dep_y = perso.Get_y - WINDOW_H/2;
    } else {
        dep_y = 0;
    }
}

Screen *Game::Get_Screen(){
    return screen;
}
