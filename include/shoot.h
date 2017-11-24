#ifndef DEF_SHOOT
#define DEF_SHOOT

#include "defs.h"

void shoot(Game *game);
void addProjectile(Game *game);
Projectile *initProjectile(Game *game);
void deleteProjectile(Game *game, Projectile *projectile);

#endif
