#include "../include/move.h"

void move(Game *game, int vx, int vy)
{
  int wPerso = game->perso->w;
  int hPerso = game->perso->h;

  for (uint i=0; i<abs(vx); i++)
  {
    if (!collisionMap(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso))
    {
      game->perso->x+=abs(vx)/vx;/*si le pixel suivant est vide, on fait avancer le perso*/
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

void gravite(Game *game, Perso *perso)
{

    perso->vSpeed += GRAVITE;
    if (perso->vSpeed > VDOWN)
    {
      perso->vSpeed = VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
    }

    for (uint i=0; i<abs(perso->vSpeed); i++)
    {
      if (collisionMap(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          game->perso->w, game->perso->h))//si collision avec element du decor
      {
        perso->vSpeed = 0;
        perso->hJumpAct = perso->hJump;//on stoppe

        if (collisionMap(game, perso->x, perso->y + 1,
            game->perso->w, game->perso->h))//si c'etait le sol
        {
          perso->hJumpAct = 0;//on remet le compteur de saut à 0
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
