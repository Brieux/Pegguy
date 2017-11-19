#include "../include/move.h"

void move(Game *game, int vx, int vy)
{
  int wPerso = game->perso->w;
  int hPerso = game->perso->h;
  DynObj *dynObj = NULL;

  for (uint i=0; i<abs(vx); i++)
  {
    if (!collisionMap(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso))
    {
      if ((dynObj = collisionMapObj(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso, 0)) != 0)
      {
        switch (dynObj->type)
        {
          case BOX :
            if (!collisionMap(game, dynObj->x + abs(vx)/vx,dynObj->y, dynObj->w, dynObj->h) &&
                !collisionMapObj(game, dynObj->x + abs(vx)/vx,dynObj->y, dynObj->w, dynObj->h, dynObj) &&
                game->perso->interact)
            {
              game->perso->x+=abs(vx)/vx;
              dynObj->x+=abs(vx)/vx;

            }
            break;
        }
      }
      else
      {
        game->perso->x+=abs(vx)/vx;/*si le pixel suivant est vide, on fait avancer le perso*/
        if ((dynObj = collisionMapObj(game, game->perso->x - abs(vx)/vx*2, game->perso->y, wPerso, hPerso, 0)) != 0 &&
             game->perso->interact)
        {
          dynObj->x+=abs(vx)/vx;
        }
      }
    }
    else
    {
      i = abs(vx);
    }
  }
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  w1--, w2--, h1--, h2--;
  return !(x1+w1<x2 || x1>x2+w2 || y1+h1<y2 || y1>y2+h2);//collision rectangulaire basique
}

bool collisionMap(Game *game, int x1, int y1, int w1, int h1)
{
  for (int x=0; x<game->wmap; x++)
  {
    for (int y=0; y<game->hmap; y++)
    {
      if (game->map[x][y]->solid)/*on teste toutes les collisions solides des cases de la map*/
      {
        if (collision(x1, y1, w1, h1, game->map[x][y]->x, game->map[x][y]->y,
                                       game->map[x][y]->w, game->map[x][y]->h))
        {
          return true;
        }
      }
    }
  }
  return false;
}

DynObj *collisionMapObj(Game *game, int x1, int y1, int w1, int h1, DynObj *dynObj)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->active && game->mapObj[i]->solid)
    {     /*on teste toutes les collisions solides des objets dyn de la map*/
      if (collision(x1, y1, w1, h1, game->mapObj[i]->x, game->mapObj[i]->y,
                                     game->mapObj[i]->w, game->mapObj[i]->h))
      {
        if (game->mapObj[i] != dynObj)
        {
          return game->mapObj[i];
        }
      }
    }
  }
  return 0;
}

void graviteObj(Game *game)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    game->mapObj[i]->vSpeed += GRAVITE;
    if (game->mapObj[i]->vSpeed > VDOWN)
    {
      game->mapObj[i]->vSpeed = VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
    }
    for (uint k=0; k<abs(game->mapObj[i]->vSpeed); k++)
    {
      if (collisionMap(game, game->mapObj[i]->x, game->mapObj[i]->y + abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed,
          game->mapObj[i]->w, game->mapObj[i]->h) || //si collision avec element du decor
          collisionMapObj(game, game->mapObj[i]->x, game->mapObj[i]->y + abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed,
          game->mapObj[i]->w,game->mapObj[i]->h, game->mapObj[i]))//si collision avec objet dynamique
      {
        game->mapObj[i]->vSpeed = 0;
      }
      else
      {
        game->mapObj[i]->y += abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed;//sinon on modifie la position du perso
      }
    }
  }
}

void gravite(Game *game, Perso *perso)
{
    DynObj *dynObj = NULL;
    perso->vSpeed += GRAVITE;
    if (perso->vSpeed > VDOWN)
    {
      perso->vSpeed = VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
    }

    for (uint i=0; i<abs(perso->vSpeed); i++)
    {
      if (collisionMap(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          game->perso->w, game->perso->h) || //si collision avec element du decor
          collisionMapObj(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          game->perso->w, game->perso->h, 0))//si collision avec objet dynamique
      {
        perso->vSpeed = 0;
        perso->hJumpAct = perso->hJump;//on stoppe

        if (collisionMap(game, perso->x, perso->y + 1,
            game->perso->w, game->perso->h) ||
            (dynObj = collisionMapObj(game, perso->x, perso->y + 1,
            game->perso->w, game->perso->h, 0)))//si c'etait le sol
        {
          perso->hJumpAct = 0;//on remet le compteur de saut à
          if (dynObj)
          {
            switch (dynObj->type)
            {
              case BOX_DESTROYABLE_EMPTY :
                dynObj->active = false;
                break;
            }
          }
        }
      }
      else
      {
        perso->y += abs(perso->vSpeed)/perso->vSpeed;//sinon on modifie la position du perso
      }
    }
}

void jump(Perso *perso)
{
  perso->vSpeed = -perso->vJump;
  perso->hJumpAct++;
}
