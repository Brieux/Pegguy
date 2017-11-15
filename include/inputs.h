#ifndef DEF_INPUTS
#define DEF_INPUTS

#include "defs.h"

Input *generateInput();//crée la structure input
void inputs(Game *game);//gère les inputs
void updateEvents(Input *input);//met à jour les actions
void updateInputs(Game *game);//met à jour les inputs

#endif
