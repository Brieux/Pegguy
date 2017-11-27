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
  game->numDialogue = 0;
  game->dialogue = false;
  game->endDialogue = false;
  game->first_mob = NULL;
  game->choice = 0;
  game->nbChoices = 0;
  game->background = loadTexture("../graphics/background.png", game->screen->pRenderer);
  game->menuPointer = loadTexture("../graphics/menuPointer.png", game->screen->pRenderer);
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
  //Chargement des textures
  perso->image[0] = loadTexture("../graphics/peggy1.png", game->screen->pRenderer);
  perso->image[1] = loadTexture("../graphics/peggy1.png", game->screen->pRenderer);
  perso->image[2] = loadTexture("../graphics/peggy1.png", game->screen->pRenderer);
  perso->image[3] = loadTexture("../graphics/peggy1.png", game->screen->pRenderer);
  perso->image[4] = loadTexture("../graphics/peggy1.png", game->screen->pRenderer);
  //A changer selon les maps je suppose ?
  perso->w = 32;
  perso->h = 64;
  perso->x = 96;
  perso->y = 200;
  perso->waitShoot = 0;
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
  perso->invincible = 0;
  perso->hp = 3;
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
  FILE *file = fopen("../texts/level1.txt", "r");
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
  dynObj->linked = false;
  dynObj->active = active;
  dynObj->gravite = gravite;
  dynObj->vSpeed = vSpeed;
  dynObj->hSpeed = hSpeed;
  dynObj->image = loadTexture(image, game->screen->pRenderer);
  dynObj->link = NULL;
  dynObj->count = 0;
  dynObj->dialogue = false;

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

  int xLink, yLink;
  int i = 0;
  for (int y=0; y<game->hmap; y++)
  {
    for (int x=0; x<game->wmap; x++)
    {
      game->map[x][y]->type = fgetc(file);//on copie la grille
      fscanf(file, ",x:%dy:%d/", &xLink, &yLink);

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
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX_DESTROYABLE_EMPTY :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_EMPTY, x*32, y*32, 64, 64,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX_DESTROYABLE_BALL :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_BALL, x*32, y*32, 64, 64,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX_DESTROYABLE_DUMMY_LAUNCHER :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_DUMMY_LAUNCHER, x*32, y*32, 64, 64,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BALL :
          game->mapObj[i] = initDynObj(game, BALL, x*32, y*32, 16, 16,
                                        false, true, false, 0, 0, "../graphics/bille.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case DUMMY_LAUNCHER :
          game->mapObj[i] = initDynObj(game, DUMMY_LAUNCHER, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/dummy_launcher.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case TARGET :
          game->mapObj[i] = initDynObj(game, TARGET, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/target.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case DOOR :
          game->mapObj[i] = initDynObj(game, DOOR, x*32, y*32, 32, 64,
                                        true, true, false, 0, 0, "../graphics/door.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case CIRCLE:
          game->mapObj[i] = initDynObj(game, CIRCLE, x*32, y*32, 32, 32,
                                        false, true, true, 0, 0, "../graphics/circle.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case TRIANGLE:
          game->mapObj[i] = initDynObj(game, TRIANGLE, x*32, y*32, 32, 32,
                                        false, true, true, 0, 0, "../graphics/triangle.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case SQUARE:
          game->mapObj[i] = initDynObj(game, SQUARE, x*32, y*32, 32, 32,
                                        false, true, true, 0, 0, "../graphics/square.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case CIRCLE_BASE:
          game->mapObj[i] = initDynObj(game, CIRCLE_BASE, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/circle_base.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case TRIANGLE_BASE:
          game->mapObj[i] = initDynObj(game, TRIANGLE_BASE, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/triangle_base.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case SQUARE_BASE:
          game->mapObj[i] = initDynObj(game, SQUARE_BASE, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/square_base.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case NPC1 :
          game->mapObj[i] = initDynObj(game, NPC1, x*32, y*32, 32, 64,
                                        false, true, false, 0, 0, "../graphics/npc.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          game->mapObj[i]->content = "Bonjour, je s'appelle Groot\n"
                                      "Je suis ici pour vous guider\n"
                                      "Etes-vous d'accord ?\\3"
                                        "Et puis quoi encore ?\n"
                                        "Hey ! Listen !\n"
                                        "Ca me va, je suis un assiste\\"
                                      "Bien, votre choix est fait\n"
                                      "Enfin, il me semble ?\\2"
                                        "Oui\n"
                                        "Non\0";
          i++;
          break;
        default :
          game->map[x][y]->solid = false;
      }
    }
    jumpLine(file);
  }
  int j = 0;
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->xLink != -1 && game->mapObj[i]->yLink != -1)
    {
      for (int k=0; k<game->nbDynObj; k++)
      {
        if (game->mapObj[k]->x == game->mapObj[i]->xLink*32 && game->mapObj[k]->y == game->mapObj[i]->yLink*32)
        {
          game->mapObj[i]->link = game->mapObj[k];
          game->mapObj[k]->count++;
          game->mapObj[k]->linked = true;
          j++;
        }
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
