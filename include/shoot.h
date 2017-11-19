#ifndef DEF_SHOOT
#define DEF_SHOOT

#include "defs.h"

void shoot(Game *game);
Projectile *addProjectile(Game *game, Projectile *projectile);
Projectile *initProjectile(Game *game);
Projectile *deleteProjectile(Game *game, Projectile *projectile);

#endif
