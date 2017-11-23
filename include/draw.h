#ifndef DEF_DRAW
#define DEF_DRAW

#include "defs.h"

void calcul_dep(int *dep_x, int *dep_y, Game *game);
void print_line(Game *game, int x, int y, char *debug_text);
void consol_d(Game *game, int dep_x, int dep_y);
void drawGame(Game *game);//affiche tous les sprites du jeu game
void drawDialogueNPCs(Game *game, int dep_x, int dep_y);
void drawMap(Game *game);
void drawProjectiles(Game *game, int dep_x, int dep_y);
void drawHUD(Game *game);
void clearScreen(Screen *screen);//efface l'écran screen
void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *pRenderer);//affiche une image à x y sur la surface pRenderer

#endif
