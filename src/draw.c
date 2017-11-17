#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawMap(game);
  drawImage(game->perso->image, game->perso->x, game->perso->y, game->screen->pRenderer);
  SDL_RenderPresent(game->screen->pRenderer);
}

void drawMap(Game *game)
{
  for (int x=0; x<game->wmap; x++)
  {
    for (int y=0; y<game->hmap; y++)
    {
      switch (game->map[x][y]->type)
      {
        case GROUND:
          drawImage(game->map[x][y]->image, x*32, y*32, game->screen->pRenderer);
          break;
      }
    }
  }
}

void clearScreen(Screen *screen)
{
  SDL_SetRenderDrawColor(screen->pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(screen->pRenderer);
}

void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *pRenderer)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(pRenderer, texture, NULL, &dest);
}
