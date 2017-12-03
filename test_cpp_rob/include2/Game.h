#ifndef GAME_H
#define GAME_H

#include "defs.h"

class Game{
    private:
        int wmap;
        int hmap;
        int level;
        Screen *screen;

    public:
        Game(int id_level = 0, const char* title = "");
        ~Game();
};

#endif
