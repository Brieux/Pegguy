#ifndef DEF_LOAD
#define DEF_LOAD

#include "defs.h"

Game *loadGame();//crée une partie
Perso *loadPerso(Game *game);//crée un perso
SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer);//charge l'image
void loadMap(Game *game);
void initMap(FILE *file, Game *game);
int jumpLine(FILE *file);
void searchLevel(FILE *file, int level);

#endif
