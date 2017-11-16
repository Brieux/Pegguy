#include "../include/move.h"

void move(Game *game, int *x, int *y, int vx, int vy)
{
  for (uint i=0; i<abs(vx); i++)
  {
    if (!collision(game->perso->x + abs(vx)/vx, game->perso->y, game->perso->w, game->perso->h,
                   -1, 0, 0, WINDOW_H) &&
        !collision(game->perso->x + abs(vx)/vx, game->perso->y, game->perso->w, game->perso->h,
                   WINDOW_W, 0, 0, WINDOW_H))
    {
      *x+=abs(vx)/vx;
    }
  }
  for (uint i=0; i<abs(vy); i++)
  {
    if (!collision(game->perso->x, game->perso->y + abs(vy)/vy, game->perso->w, game->perso->h,
                   0, 0, 0, WINDOW_H))
    {
      *y+=abs(vy)/vy;
    }
  }
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  return !(x1+w1<x2 || x1>x2+w2 || y1+h1<y2 || y1>y2+h2);
}
