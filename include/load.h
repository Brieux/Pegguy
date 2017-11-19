#ifndef DEF_LOAD
#define DEF_LOAD

#include "defs.h"

Game *loadGame(int n_map);//crée une partie
HUD *initHUD(Game *game);
Perso *loadPerso(Game *game);//crée un perso
SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer);//charge l'image
void loadFont(Game *game);
void loadMap(Game *game);
DynObj *initDynObj(Game *game, int type, int x, int y, int w, int h, bool solid,
                      bool active, bool gravite, int vSpeed, char *image);
void initBlocMap(Game *game, Bloc *bloc, int x, int y, char *image);
void initMap(FILE *file, Game *game);
int jumpLine(FILE *file);
void searchLevel(FILE *file, int level);

#endif
