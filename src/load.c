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
  game->hud = initHUD(game);
  game->projectiles = NULL;
  game->level = n_map;
  loadMap(game);
  loadFont(game);

  return game;
}

HUD *initHUD(Game *game)
{
  HUD *hud = malloc(sizeof(HUD));
  hud->ball = loadTexture("../graphics/bille.png", game->screen->pRenderer);
  hud->nbBalls = 0;
  hud->xBall = 200;
  hud->yBall = 40;

  hud->hearts = loadTexture("../graphics/Heart.png", game->screen->pRenderer);
  hud->xHearts = 40;
  hud->yHearts = 40;

  return hud;
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
  perso->direction = RIGHT;
  perso->hSpeed = 5;
  perso->vSpeed = 0;
  perso->vJump = 13;
  perso->hJump = 13;
  perso->hJumpAct = 0;
  perso->interact = 0;
  perso->hand = NULL;
  perso->sizeEquip = 0;
  perso->equip = malloc(perso->sizeEquip*sizeof(DynObj*));

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

DynObj *initDynObj(Game *game, int type, int x, int y, int w, int h, bool solid,
                      bool active, bool gravite, int vSpeed, int hSpeed, char *image)
{
  DynObj *dynObj = malloc(sizeof(DynObj));
  dynObj->type = type;
  dynObj->x = x;
  dynObj->y = y;
  dynObj->w = w;
  dynObj->h = h;
  dynObj->solid = solid;
  dynObj->active = active;
  dynObj->gravite = gravite;
  dynObj->vSpeed = vSpeed;
  dynObj->hSpeed = hSpeed;
  dynObj->image = loadTexture(image, game->screen->pRenderer);
  dynObj->link = NULL;
  dynObj->count = 0;

  return dynObj;
}

void initBlocMap(Game *game, Bloc *bloc, int x, int y, char *image)
{
  bloc->solid = true;
  bloc->image = loadTexture(image, game->screen->pRenderer);
  bloc->w = 32;
  bloc->h = 32;
  bloc->x = x*32;
  bloc->y = y*32;
}

void initMap(FILE *file, Game *game)
{
  fscanf(file, "x:%d y:%d", &game->wmap, &game->hmap);//on recupere la taille de la grille
  jumpLine(file);//puis on passe à la ligne suivante
  fscanf(file, "nbDynObj:%d", &game->nbDynObj);//on recupere le nombre d'objets dynamiques
  jumpLine(file);//puis on passe à la ligne suivante

  game->mapObj = calloc(game->nbDynObj, sizeof(DynObj));//alloue tableau objets dynamiques
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

      switch (game->map[x][y]->type)     //lue dans le fichier
      {

        case GROUND :                   //case sol
          initBlocMap(game, game->map[x][y], x, y, "../graphics/Dirt.png");
          break;
        case GROUND_2 :                   //case sol
          initBlocMap(game, game->map[x][y], x, y, "../graphics/Dirt_2.png");
          break;
        case BOX :
          game->mapObj[i] = initDynObj(game, BOX, x*32, y*32, 64, 64, true, true, true, 0, 0,
                                        "../graphics/box.png");
          i++;
          break;
        case BOX_DESTROYABLE_EMPTY :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_EMPTY, x*32, y*32, 64, 64,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          i++;
          break;
        case BALL :
          game->mapObj[i] = initDynObj(game, BALL, x*32, y*32, 16, 16,
                                        false, true, false, 0, 0, "../graphics/bille.png");
          i++;
          break;
        case DUMMY_LAUNCHER :
          game->mapObj[i] = initDynObj(game, DUMMY_LAUNCHER, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/dummy_launcher.png");
          i++;
          break;
        case TARGET :
          game->mapObj[i] = initDynObj(game, TARGET, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/target.png");
          i++;
          break;
        case DOOR :
          game->mapObj[i] = initDynObj(game, DOOR, x*32, y*32, 32, 64,
                                        true, true, false, 0, 0, "../graphics/door.png");
          i++;
          break;
        default :
          game->map[x][y]->solid = false;
      }
    }
    jumpLine(file);
  }
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i] && game->mapObj[i]->type == TARGET)
    for (int k=0; k<game->nbDynObj; k++)
    {
      if (game->mapObj[k] && game->mapObj[k]->type == DOOR)
      {
        game->mapObj[i]->link = game->mapObj[k];
        game->mapObj[k]->count++;
        k = game->nbDynObj;
      }
    }
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
