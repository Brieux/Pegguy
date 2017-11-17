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
  game->wmap = 30;
  game->hmap = 20;
  game->map = malloc(game->wmap*sizeof(Bloc));
  if (!game->map)
  {
    printf("Unable to malloc map\n");
    exit(EXIT_FAILURE);
  }

  //Mise en place de la grille
  //Ici on parcour toute les valeurs de X
  for (uint i=0; i<game->wmap; i++)
  {
    //On alloc à chaque case le tableau qui contient Y Bloc*
    game->map[i] = malloc(game->hmap*sizeof(Bloc));
    if (!game->map[i])  //On test...
    {
      printf("Unable to malloc map %d\n", i);
      exit(EXIT_FAILURE);
    }

    //On alloc ces Y blocs
    for (uint k=0; k<game->hmap; k++)
    {
      game->map[i][k] = malloc(sizeof(Bloc));
      if (!game->map[i][k]){
        fprintf(stderr, "Unable to alloc case %d %d on the map\n", i, k);
        exit(EXIT_FAILURE);
      }
      game->map[i][k]->type = EMPTY;
    }
    
  }
  
  //Juste un test
  game->map[0][0]->type = GROUND;

  return game;
}


Perso *loadPerso(Game *game)
{
  Perso *perso = malloc(sizeof(Perso));
  if (!perso){
    fprintf(stderr, "Unable to alloc perso in loadPerso\n");
    exit(EXIT_FAILURE);
  }
  perso->image = loadTexture("../graphics/perso.png", game->screen->pRenderer);
  //A changer celon les maps je suppose ?
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
