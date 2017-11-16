#include "../include/load.h"

Game *loadGame()
{
  Game *game = malloc(sizeof(Game));
  game->screen = initScreen("They Come in Peace");
  game->perso = loadPerso(game);
  game->input = generateInput();
  game->wmap = 30;
  game->hmap = 20;
  game->map = malloc(game->wmap*sizeof(Bloc));
  if (!game->map)
  {
    printf("Unable to malloc map\n");
    exit(EXIT_FAILURE);
  }
  for (uint i=0; i<game->wmap; i++)
  {
    game->map[i] = malloc(game->hmap*sizeof(Bloc));
    for (uint k=0; k<game->hmap; k++)
    {
      game->map[i][k] = malloc(sizeof(Bloc));
    }
    if (!game->map[i])
    {
      printf("Unable to malloc map %d\n", i);
      exit(EXIT_FAILURE);
    }
  }
  for (int x=0; x<game->wmap; x++)
  {
    for (int y=0; y<game->hmap; y++)
    {
      game->map[x][y]->type = EMPTY;
    }
  }
  game->map[0][0]->type = GROUND;

  return game;
}


Perso *loadPerso(Game *game)
{
  Perso *perso = malloc(sizeof(Perso));
  perso->image = loadTexture("../graphics/perso.png", game->screen->pRenderer);
  perso->w = 32;
  perso->h = 64;
  perso->x = 96;
  perso->y = 96;
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
