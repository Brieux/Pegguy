#ifndef DEF_SCREEN
#define DEF_SCREEN

#include "defs.h"

void error(char *cmd);
Screen *initScreen(char *title);
void freeAll(Game *game);
void quitSDL(Screen *screen);

#endif
