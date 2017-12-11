#include "../include/shoot.h"


//listes chainees basiques, d'ailleurs faudrait les rendre universelles et pas
//focalisees sur les projectiles
void shoot(Game *game)
{
  if (game->perso->waitShoot==0)
  {
    addProjectile(game);
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
  if (!projectile)
  {
    error("Unable to malloc projectile");
  }

  projectile->following = NULL;
  char *image = "";
  int hSpeed, vSpeed, type, x, y;
  bool gravite;

  switch (game->perso->hand->type)
  {
    case DUMMY_LAUNCHER :
      game->perso->waitShoot = DELAY_SHOOT_DUMMY;
      switch (game->perso->direction)
      {
        case RIGHT :
          hSpeed = 6;
          x = game->perso->x + 33;
          break;
        case LEFT :
          hSpeed = -6;
          x = game->perso->x - 25;
          break;
      }
      switch (game->perso->direction)
      {
        case RIGHT :
            image = "../graphics/dummy_launcher/dummyupright.png";
            break;
        case LEFT :
            image = "../graphics/dummy_launcher/dummyupleft.png";
            break;
      }
      y = game->perso->y + 14;
      vSpeed = -15;
      type = DUMMY;
      gravite = true;
      break;
    case GHOST_GUN :
      game->perso->waitShoot = DELAY_SHOOT_PLASMA;
      switch (game->perso->direction)
      {
        case RIGHT :
          hSpeed = 8;
          x = game->perso->x + 20;
          break;
        case LEFT :
          hSpeed = -8;
          x = game->perso->x - 12;
          break;
      }
      switch (game->perso->direction)
      {
        case RIGHT :
            image = "../graphics/ghost_gun/plasma.png";
            break;
        case LEFT :
            image = "../graphics/ghost_gun/plasma.png";
            break;
      }
      y = game->perso->y + 38;
      vSpeed = 0;
      type = PLASMA;
      gravite = false;
      break;
  }
  projectile->dynObj = initDynObj(game, type, x, y,
                                          16, 16, false, true, gravite, vSpeed, hSpeed,
                                           image);
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

    if (projectile == game->projectiles && !game->projectiles->following){
        free(projectile->dynObj);
        free(projectile);
        game->projectiles = NULL;
    } else if (projectile == game->projectiles && game->projectiles->following){
        game->projectiles = game->projectiles->following;
    } else {
        if (projectile->following){
            p_projectile->following = projectile->following;
        } else {
            p_projectile->following = NULL;
        }

        free(projectile->dynObj);
        free(projectile);
    }
}
