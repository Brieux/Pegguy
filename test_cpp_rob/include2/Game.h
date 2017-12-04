#ifndef GAME_H
#define GAME_H

#include "defs.h"

class Game{
    private:
        int wmap;
        int hmap;
        int level;
        Screen *screen;
        Perso *perso;   //A Faire
    public:
        Game(int id_level = 0, const char* title = "", int wmap = 0, int hmap = 0);
        ~Game();
        void Calcul_Dep(int &dep_x, int &dep_y);
        Screen *Get_Screen();
};

#endif
