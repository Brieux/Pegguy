#include "../include/load.h"

//Génération du game
Game *loadGame(int n_map)
{
  Game *game = malloc(sizeof(Game));
  if (!game){
    error("Unable to alloc game.");
  }
  game->screen = initScreen("Peggy");
  game->perso = loadPerso(game);
  game->input = generateInput();
  game->level = n_map;
  loadMap(game);
  loadFont(game);

  return game;
}

void loadFont(Game *game){
  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  game->font = malloc(sizeof(TTF_Font *));
  game->font = TTF_OpenFont("../graphics/HACKED.ttf", 20);
  if (!game->font){
    fprintf(stderr, "Unable to load font: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

Perso *loadPerso(Game *game)
{
  Perso *perso = malloc(sizeof(Perso));
  if (!perso){
    fprintf(stderr, "Unable to alloc perso in loadPerso\n");
    exit(EXIT_FAILURE);
  }
  perso->nb_frame = 5;
  perso->image = malloc(perso->nb_frame * sizeof(SDL_Texture*));

  if (!perso->image){
    fprintf(stderr, "Unable to alloc image in perso\n");
    exit(EXIT_FAILURE);
  }

  perso->image[0] = loadTexture("../graphics/perso_1.png", game->screen->pRenderer);
  perso->image[1] = loadTexture("../graphics/perso_2.png", game->screen->pRenderer);
  perso->image[2] = loadTexture("../graphics/perso_3.png", game->screen->pRenderer);
  perso->image[3] = loadTexture("../graphics/perso_4.png", game->screen->pRenderer);
  perso->image[4] = loadTexture("../graphics/perso_5.png", game->screen->pRenderer);
  //A changer selon les maps je suppose ?
  perso->w = 32;
  perso->h = 64;
  perso->x = 96;
  perso->y = 200;
  perso->hSpeed = 5;
  perso->vSpeed = 0;
  perso->vJump = 13;
  perso->hJump = 13;
  perso->hJumpAct = 0;

  return perso;
}

SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer)
{
  SDL_Surface *surface = IMG_Load(image);//on charge la surface
  SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);// puis la texture correspondante
  SDL_FreeSurface(surface);

  return texture;
}

void loadMap(Game *game)
{
  FILE *file = fopen("../texts/levels.txt", "r");
  if (!file)
  {
    error("Unable to open levels.txt");
  }

  searchLevel(file, game->level);
  initMap(file, game);

  fclose(file);

}

void initMap(FILE *file, Game *game)
{
  fscanf(file, "x:%d y:%d", &game->wmap, &game->hmap);//on recupere la taille de la grille
  jumpLine(file);//puis on passe à la ligne suivante
  fscanf(file, "nbDynObj:%d", &game->nbDynObj);//on recupere le nombre d'objets dynamiques
  jumpLine(file);//puis on passe à la ligne suivante

  game->mapObj = malloc(game->nbDynObj*sizeof(DynObj));//alloue tableau objets dynamiques
  if (!game->mapObj)
  {
    error("Unable to malloc map");
  }
  game->map = malloc(game->wmap*sizeof(Bloc*));//alloue tableau 2 dimensions map
  if (!game->map)
  {
    error("Unable to malloc map");
  }

  for (uint i=0; i<game->wmap; i++)//pour chaque case en abscisse de la map
  {
    game->map[i] = malloc(game->hmap*sizeof(Bloc*));
    //on alloue un espace suffisant pour un tableau en ordonnee
    if (!game->map[i])
    {
      printf("Unable to malloc map %d\n", i);
      exit(EXIT_FAILURE);
    }
    for (uint k=0; k<game->hmap; k++)
    {
      game->map[i][k] = malloc(sizeof(Bloc));//et pour chaque case on initialise un Bloc
    }
  }

  int i = 0;
  for (int y=0; y<game->hmap; y++)
  {
    for (int x=0; x<game->wmap; x++)
    {
      game->map[x][y]->type = fgetc(file);//on copie la grille

      printf("x:%d y:%d\n", x, y);
      switch (game->map[x][y]->type)     //lue dans le fichier
      {

        case GROUND :                   //case sol
          puts("ground");
          game->map[x][y]->solid = true;
          game->map[x][y]->image = loadTexture("../graphics/bloc.png", game->screen->pRenderer);
          game->map[x][y]->w = 32;
          game->map[x][y]->h = 32;
          game->map[x][y]->x = x*32;
          game->map[x][y]->y = y*32;
          break;
        case BOX :
          puts("box");
          game->map[x][y]->solid = false;
          game->map[x][y]->type = EMPTY;
          /*game->mapObj[i]->box = malloc(sizeof(Box));
          if (!game->mapObj[i])
          {
            error("Unable to malloc mapObj");
          }*/
          game->mapObj[i] = malloc(sizeof(DynObj));
          game->mapObj[i]->solid = true;
          game->mapObj[i]->x = x*32;
          game->mapObj[i]->y = y*32;
          game->mapObj[i]->w = 64;
          game->mapObj[i]->h = 64;
          game->mapObj[i]->image = loadTexture("../graphics/box.png", game->screen->pRenderer);
          i++;
          puts("truc");
          break;
        default :
          puts("EMPTY");
          game->map[x][y]->solid = false;
      }
    }
    jumpLine(file);
  }
  puts("coucou2");
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
