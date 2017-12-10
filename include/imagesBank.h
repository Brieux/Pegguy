#ifndef DEF_IMAGESBANK
#define DEF_IMAGESBANK

#include "defs.h"

void loadImagesBank(Game *game);
int hash(ImagesBank *bank, char *name);
void placeBank(char *name, Game *game);
int searchBank(Game *game, char *name);
SDL_Texture *getImage(Game *game, char *name);
void printBank(Game *game);
void freeImagesBank(Game *game);

#endif
