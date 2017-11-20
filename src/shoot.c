#include "../include/shoot.h"


//listes chainees basiques, d'ailleurs faudrait les rendre universelles et pas
//focalisees sur les projectiles
void shoot(Game *game)
{
  game->projectiles = addProjectile(game, game->projectiles);
}

Projectile *addProjectile(Game *game, Projectile *projectile)
{
  if (!projectile)
  {
    projectile = initProjectile(game);
    return projectile;
  }

  Projectile *projectile2 = projectile;

  int i = 0;
  while (projectile->following)
  {
    i++;
    projectile = projectile->following;
  }
  projectile->following = initProjectile(game);

  return projectile2;
}

Projectile *initProjectile(Game *game)
{
  Projectile *projectile = malloc(sizeof(Projectile));
  projectile->following = NULL;
  int hSpeed;
  switch (game->perso->direction)
  {
    case RIGHT :
      hSpeed = 6;
      break;
    case LEFT :
      hSpeed = -6;
      break;
  }
  projectile->dynObj = initDynObj(game, DUMMY, game->perso->x, game->perso->y,
                                      16, 16, false, true, true, -15, hSpeed, "../graphics/dummy.png");

  return projectile;
}

Projectile *deleteProjectile(Game *game, Projectile *projectile)
{
  Projectile *projectile2 = game->projectiles;
  if (projectile2 == projectile)
  {
    projectile = projectile2->following;
    free(projectile2->dynObj);
    free(projectile2);
    return projectile;
  }
  while (projectile2->following != projectile)
  {
    projectile2 = projectile2->following;
  }
  projectile2->following = projectile->following;
  free(projectile->dynObj);
  free(projectile);

  return game->projectiles;
}
