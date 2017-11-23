#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef unsigned int uint;

enum {EMPTY=48/*0*/, GROUND/*1*/, GROUND_2/*2*/, BOX_DESTROYABLE_EMPTY/*3*/, BALL/*4*/,
      BOX/*5*/, DUMMY_LAUNCHER/*6*/, DUMMY/*7*/, TARGET/*8*/, DOOR/*9*/,
      BOX_DESTROYABLE_BALL=65/*A*/, BOX_DESTROYABLE_DUMMY_LAUNCHER/*B*/, NPC1/*C*/};
enum {RIGHT, LEFT, UP, DOWN};

typedef struct Screen
{
  SDL_Window *pWindow;
  SDL_Renderer *pRenderer;
}Screen;

typedef struct Input
{
  int xCursor, yCursor;
  bool quit;
  bool key[SDL_NUM_SCANCODES];
  bool mouse[5];
}Input;

typedef struct DynObj
{
  int x, y, w, h;
  int vSpeed, hSpeed;
  int type, count;
  bool solid, active, gravite;
  char *content;
  SDL_Texture *image;
  struct DynObj *link;
}DynObj;

typedef struct Projectile
{
  DynObj *dynObj;
  struct Projectile *following;
}Projectile;

typedef struct Perso
{
  int x, y ,w ,h;
  int index, hp;
  int hSpeed, vSpeed;
  int hJump, vJump;
  int hJumpAct;
  int direction;
  int waitShoot;
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
  SDL_Texture *background;
  Input *input;
  Perso *perso;
  Bloc ***map;
  DynObj **mapObj;
  Projectile *projectiles;
  struct mob *first_mob;
  TTF_Font *font;
}Game;

typedef struct Editor
{
  int wmap, hmap;
  int dep_x, dep_y;
  int nbDynObj;
  int nbBlocs;
  int typeAct;
  int level;
  DynObj **blocs;
  DynObj ***map;
  Screen *screen;
  SDL_Texture *background;
  Input *input;
}Editor;

#endif
