#ifndef DEF_MOVE
#define DEF_MOVE

#include "defs.h"

void move(Game *game, int vx, int vy);
bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
bool collisionMap(Game *game, int x1, int y1, int w1, int h1);
void gravite(Perso *perso);
void jump(Perso *perso);

#endif
