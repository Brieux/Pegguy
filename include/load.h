#ifndef DEF_LOAD
#define DEF_LOAD

#include "defs.h"

Game *loadGame();//crée une partie
Perso *loadPerso(Game *game);//crée un perso
SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer);//charge l'image

#endif
