#ifndef DEF_SCREEN
#define DEF_SCREEN

#include "defs.h"

void error(char *cmd);
Screen *initScreen(char *title);
void freeDynObj(DynObj *dynObj);
void freeAll(Game *game);
void quitSDL(Screen *screen);

#endif
