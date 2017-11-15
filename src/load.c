#include "../include/load.h"

Game *loadGame()
{
  Game *game = malloc(sizeof(Game));
  game->screen = initScreen("They Come in Peace");
  game->perso = loadPerso(game);
  game->input = generateInput();

  return game;
}

Perso *loadPerso(Game *game)
{
  Perso *perso = malloc(sizeof(Perso));
  perso->image = loadTexture("../graphics/perso.png", game->screen->pRenderer);
  perso->w = 32;
  perso->h = 64;
  perso->x = 100;
  perso->y = 100;
  perso->hSpeed = 5;
  perso->vSpeed = 5;

  return perso;
}

SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer)
{
  SDL_Surface *surface = IMG_Load(image);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}
