#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef unsigned int uint;

enum {EMPTY=48/*0*/, GROUND/*1*/, GROUND_2/*2*/, BOX_DESTROYABLE_EMPTY/*3*/, BALL/*4*/,
      BOX/*5*/, DUMMY_LAUNCHER/*6*/, DUMMY/*7*/, TARGET/*8*/, DOOR/*9*/,
      BOX_DESTROYABLE_BALL=65/*A*/, BOX_DESTROYABLE_DUMMY_LAUNCHER/*B*/, NPC1/*C*/,
      SQUARE/*D*/, CIRCLE/*E*/, TRIANGLE/*F*/, SQUARE_BASE/*G*/, CIRCLE_BASE/*H*/,
      TRIANGLE_BASE/*I*/, MOBILE_PLATFORM=75/*K*/, SECRET_GROUND};

enum {RIGHT, LEFT, UP, DOWN};

enum {CHOICE_PREVIOUS, CHOICE_NEXT, NEXT};

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
  bool solid, active, gravite, dialogue;
  char *content;
  SDL_Texture *image;
  int xLink, yLink;
  bool linked;
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
  bool letal, solid, interact, move;
  char *content;
  int nb_frame;
  SDL_Texture **image;
  DynObj *hand;
  int sizeEquip;
  int invincible;
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
  int numDialogue;
  int choice, nbChoices;
  bool dialogue, endDialogue;
  SDL_Texture *menuPointer;
  HUD *hud;
  Screen *screen;
  SDL_Texture *background;
  Input *input;
  Perso *perso;
  Perso *sin;
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
  bool link;
  DynObj *linker;
  DynObj **blocs;
  DynObj ***map;
  Screen *screen;
  SDL_Texture *background;
  SDL_Texture *cursorImage;
  SDL_Texture *linkImage;
  Input *input;
  TTF_Font *font;
}Editor;

#endif
