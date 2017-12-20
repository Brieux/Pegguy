#include "../include/load.h"

//Génération du game
Game *loadGame(int n_map)
{
  Game *game = malloc(sizeof(Game));
  if (!game){
    error("Unable to alloc game.");
  }
  game->screen = initScreen("Peggy");
  loadImagesBank(game);
  game->perso = loadPerso(game);
  game->sin = loadSin(game); 
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
  game->background = "../graphics/background.png";
  game->menuPointer = "../graphics/menu_pointer.png";
  loadMap(game);
  loadFont(game);

  return game;
}

HUD *initHUD(Game *game)
{
  HUD *hud = malloc(sizeof(HUD));
  if (!hud){
    error("Unable to alloc hud.");
  }
  hud->ball = "../graphics/billefinale.png";
  hud->nbBalls = 0;
  hud->xBall = 200;
  hud->yBall = 40;
  hud->hearts = "../graphics/Heart.png";
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
  perso->nb_frame = 4;

  perso->image = malloc(2 * sizeof(SDL_Texture*));
  if (!perso->image){
    fprintf(stderr, "Unable to alloc image in perso\n");
    exit(EXIT_FAILURE);
  }
  perso->image[0] = malloc(perso->nb_frame * sizeof(SDL_Texture*));
  if (!perso->image[0]){
    fprintf(stderr, "Unable to alloc image[0] in perso\n");
    exit(EXIT_FAILURE);
  }
  perso->image[1] = malloc(perso->nb_frame * sizeof(SDL_Texture*));
  if (!perso->image[1]){
    fprintf(stderr, "Unable to alloc image[1] in perso\n");
    exit(EXIT_FAILURE);
  }


  //Chargement des textures
  perso->image[0][0] = "../graphics/spritepegguy/testprofildroite.png";
  perso->image[0][1] = "../graphics/spritepegguy/testprofildroitjambedroite.png";
  perso->image[0][2] = perso->image[0][0];
  perso->image[0][3] = "../graphics/spritepegguy/testprofildroitjambegauche.png";

  perso->image[1][0] = "../graphics/spritepegguy/testprofilgauche.png";
  perso->image[1][1] = "../graphics/spritepegguy/testprofilgauchejambedroite.png";
  perso->image[1][2] = perso->image[1][0];
  perso->image[1][3] = "../graphics/spritepegguy/testprofilgauchejambegauche.png";

  //A changer selon les maps je suppose ?
  perso->w = 32;
  perso->h = 64;
  perso->x = 110;  //96 was here
  perso->y = 200;
  perso->waitShoot = 0;
  perso->direction = RIGHT;
  perso->move = false;
  perso->hSpeed = 5;
  perso->vSpeed = 0;
  perso->vJump = 13;
  perso->hJump = 13;
  perso->hJumpAct = 0;
  perso->interact = 0;
  perso->hand = NULL;
  perso->sizeEquip = 0;
  perso->equip = malloc(perso->sizeEquip*sizeof(DynObj*));
  if (!perso->equip){
    error("Unable to malloc perso->equip");
  }
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
  if (!dynObj){
    error("Unable to malloc dynObj");
  }
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
  dynObj->image = image;
  dynObj->link = NULL;
  dynObj->count = 0;
  dynObj->dialogue = false;

  return dynObj;
}

void initBlocMap(Game *game, Bloc *bloc, int x, int y, char *image)
{
  bloc->solid = true;
  bloc->image = image;
  bloc->w = 32;
  bloc->h = 32;
  bloc->x = x*32;
  bloc->y = y*32;
}

void initMap(FILE *file, Game *game)
{
    fscanf(file, "x:%d y:%d", &game->wmap, &game->hmap);                  //on recupere la taille de la grille
    jumpLine(file);                                                       //puis on passe à la ligne suivante
    fscanf(file, "nbDynObj:%d", &game->nbDynObj);                         //on recupere le nombre d'objets dynamiques
    jumpLine(file);                                                       //puis on passe à la ligne suivante

    //Initialisaion de mapObj
    game->mapObj = NULL;
    if (!(game->mapObj = calloc(game->nbDynObj, sizeof(DynObj)))){
        fprintf(stderr, "Error in initMap, can't alloc memory.\n");
        exit(EXIT_FAILURE);
    }

    //Initialisation de map
    game->map = NULL;
    if (!(game->map = malloc(game->wmap * sizeof(Bloc**)))){
        fprintf(stderr, "Error in initMap, can't alloc memory.\n");
        exit(EXIT_FAILURE);
    }

    for (int x = 0; x < game->wmap; x++){
        game->map[x] = NULL;
        if (!(game->map[x] = malloc(game->hmap*sizeof(Bloc*)))){
            printf("Unable to malloc map %d\n", x);
            exit(EXIT_FAILURE);
        }
    
        for (int y = 0; y < game->hmap; y++){
            game->map[x][y] = NULL;
            if (!(game->map[x][y] = malloc(sizeof(Bloc)))){
                fprintf(stderr, "Error in initMap : Can't alloc memory for (%d,%d)\n", x, y);
                exit(EXIT_FAILURE);
            } else {
                game->map[x][y]->solid = false;
            }
        }
    }

  int xLink = 0, yLink = 0;
  int i = 0;
  for (int y=0; y<game->hmap; y++)
  {
    for (int x=0; x<game->wmap; x++)
    {
      game->map[x][y]->type = fgetc(file);//on copie la grille
      if (game->map[x][y]->type == EOF){
        fprintf(stderr, "Error in initMap, EOF\n");
        exit(EXIT_FAILURE);
      }
      fscanf(file, ",x:%dy:%d/", &xLink, &yLink);

      switch (game->map[x][y]->type)     //lue dans le fichier
      {

        case GROUND :                   //case sol
          initBlocMap(game, game->map[x][y], x, y, "../graphics/Dirt.png");
          break;
        case GROUND_2 :                   //case sol
          initBlocMap(game, game->map[x][y], x, y, "../graphics/Dirt_2.png");
          break;
        case SECRET_GROUND :                   //case sol
          game->mapObj[i] = initDynObj(game, BOX, x*32, y*32, 32, 32, false, true, false, 0, 0,
                                        "../graphics/Dirt_2.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX :
          game->mapObj[i] = initDynObj(game, BOX, x*32, y*32, 64, 64, true, true, true, 0, 0,
                                        "../graphics/box.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BRIDGE :
          game->mapObj[i] = initDynObj(game, BOX, x*32, y*32, 256, 32, true, true, true, 0, 0,
                                        "../graphics/bridge.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX_DESTROYABLE_EMPTY :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_EMPTY, x*32, y*32, 64, 96,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BOX_DESTROYABLE_BALL :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_BALL, x*32, y*32, 64, 96,
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
        case BOX_DESTROYABLE_GHOST_GUN :
          game->mapObj[i] = initDynObj(game, BOX_DESTROYABLE_GHOST_GUN, x*32, y*32, 64, 64,
                                        true, true, true, 0, 0, "../graphics/box_destroyable.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case BALL :
          game->mapObj[i] = initDynObj(game, BALL, x*32, y*32, 16, 16,
                                        false, true, false, 0, 0, "../graphics/billefinale.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case DUMMY_LAUNCHER :
          game->mapObj[i] = initDynObj(game, DUMMY_LAUNCHER, x*32, y*32, 32, 32,
                                        false, true, false, 0, 0, "../graphics/dummy_launcher/dummy_launcher.png");
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
        case MOBILE_PLATFORM :
          game->mapObj[i] = initDynObj(game, MOBILE_PLATFORM, x*32, y*32, 64, 32,
                                        true, true, false, 0, 2, "../graphics/mobile_platform.png");
          game->mapObj[i]->xLink = xLink;
          game->mapObj[i]->yLink = yLink;
          i++;
          break;
        case B1 :
          add_monster(game, B1, x*32, y*32);
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
