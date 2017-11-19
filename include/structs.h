#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef unsigned int uint;

enum {EMPTY=48, GROUND, BOX, BOX_DESTROYABLE_EMPTY, BALL, DUMMY_LAUNCHER};

typedef struct Screen
{
  SDL_Window *pWindow;
  SDL_Renderer *pRenderer;
}Screen;

typedef struct Input
{
  bool quit;
  bool key[SDL_NUM_SCANCODES];
}Input;

typedef struct DynObj
{
  int x, y, w, h;
  int vSpeed;
  int type;
  bool solid, active, gravite;
  SDL_Texture *image;
  struct DynObj *content;
}DynObj;

typedef struct Perso
{
  int x, y ,w ,h;
  int index, hp;
  int hSpeed, vSpeed;
  int hJump, vJump;
  int hJumpAct;
  bool letal, solid, interact;
  char *content;
  int nb_frame;
  SDL_Texture **image;
  DynObj *hand;
  int sizeEquip;
  DynObj **equip;

}Perso;

typedef struct Bloc
{
  int x, y, w, h;
  int type;
  bool solid;
  SDL_Texture *image;
}Bloc;

typedef struct HUD
{
  int nbBalls, xBall, yBall;
  SDL_Texture *ball;
  int xHearts, yHearts;
  SDL_Texture *hearts;
}HUD;

typedef struct Game
{
  int wmap, hmap;
  int level;
  int nbDynObj;
  HUD *hud;
  Screen *screen;
  SDL_Texture *ground;
  Input *input;
  Perso *perso;
  Bloc ***map;
  DynObj **mapObj;
  TTF_Font *font;
}Game;

#endif
