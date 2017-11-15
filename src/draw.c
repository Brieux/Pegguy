#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawImage(game->perso->image, game->perso->x, game->perso->y, game->screen->pRenderer);
  SDL_RenderPresent(game->screen->pRenderer);
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
