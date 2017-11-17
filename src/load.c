#include "../include/load.h"

//Génération du game
Game *loadGame()
{
  Game *game = malloc(sizeof(Game));
  if (!game){
    error("Unable to alloc game.");
  }
  game->screen = initScreen("Peggy");
  game->perso = loadPerso(game);
  game->input = generateInput();
  game->level = 1;
  loadMap(game);

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

void loadMap(Game *game)
{
  FILE *file = fopen("../texts/levels.txt", "r");
  if (!file)
  {
    printf("Unable to open levels.txt");
    exit(EXIT_FAILURE);
  }

  searchLevel(file, game->level);
  initMap(file, game);

  fclose(file);

}

void initMap(FILE *file, Game *game)
{
  fscanf(file, "x:%d y:%d", &game->wmap, &game->hmap);
  jumpLine(file);

  game->map = malloc(game->wmap*sizeof(Bloc));
  if (!game->map)
  {
    printf("Unable to malloc map\n");
    exit(EXIT_FAILURE);
  }
  for (uint i=0; i<game->wmap; i++)
  {
    game->map[i] = malloc(game->hmap*sizeof(Bloc));
    if (!game->map[i])
    {
      printf("Unable to malloc map %d\n", i);
      exit(EXIT_FAILURE);
    }
    for (uint k=0; k<game->hmap; k++)
    {
      game->map[i][k] = malloc(sizeof(Bloc));
    }
  }

  for (int y=0; y<game->hmap; y++)
  {
    for (int x=0; x<game->wmap; x++)
    {
      game->map[x][y]->type = fgetc(file) - 48;
      game->map[x][y]->image = loadTexture("../graphics/bloc.png", game->screen->pRenderer);
    }
    jumpLine(file);
  }
}

int jumpLine(FILE *file)
{
  char caractere;
  while ((caractere=fgetc(file))!='\n')
  {
    if (caractere==EOF)
    {
      return -1;
    }
  }
  return 1;
}

void searchLevel(FILE *file, int level)
{
  //on cherche le niveau correspondant
  int lvl_actu=0;
  while (lvl_actu!=level)
  {
    fscanf(file, "Lvl:%d", &lvl_actu);
    //tan qu'on ne trouve pas on saute une ligne
    if (jumpLine(file)==-1)
    {
      printf("Unable to find the level\n");
      exit(EXIT_FAILURE);
    }
  }
}
