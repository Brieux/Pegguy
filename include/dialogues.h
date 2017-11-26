#ifndef DEF_DIALOGUES
#define DEF_DIALOGUES

#include "defs.h"

void interactionNPC(Game *game);
void drawDialogueNPCs(Game *game, int dep_x, int dep_y);
void gestionDialogues(Game *game, int type);
void dialogue(Game *game, char *text, int dep_x, int dep_y);

#endif
