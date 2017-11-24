#include "../include/shoot.h"


//listes chainees basiques, d'ailleurs faudrait les rendre universelles et pas
//focalisees sur les projectiles
void shoot(Game *game)
{
  if (game->perso->waitShoot==0)
  {
    addProjectile(game);
    game->perso->waitShoot = DELAY_SHOOT_DUMMY;
  }
}

void addProjectile(Game *game){
    if (!game->projectiles){
      game->projectiles = initProjectile(game);
    } else {
        Projectile *p_projectile = malloc(sizeof(Projectile));
        p_projectile = game->projectiles;
        
        game->projectiles = initProjectile(game);
        game->projectiles->following = p_projectile;
    }
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

void deleteProjectile(Game *game, Projectile *projectile){
    if (!projectile || !game->projectiles){
        return;
    }
    Projectile *p_projectile = game->projectiles;
    while(p_projectile->following && p_projectile->following != projectile){
       p_projectile = p_projectile->following;
    }

    if (projectile == game->projectiles){
        free(projectile->dynObj);
        free(projectile);
        game->projectiles = NULL;
        return;
    }

    if (projectile->following){
        p_projectile->following = projectile->following;
    } else {
        p_projectile->following = NULL;
    }
    
    free(projectile->dynObj);
    free(projectile);
}


