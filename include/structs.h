#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef unsigned int uint;

enum {EMPTY=48, GROUND, BOX};

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

typedef struct Perso
{
  int x, y ,w ,h;
  int index, hp;
  int hSpeed, vSpeed;
  int hJump, vJump;
  int hJumpAct;
  bool letal, solid;
  char *content;
  void *hand;
  int nb_frame;
  SDL_Texture **image;
  void *equip[];

}Perso;

typedef struct Box
{
  int type;
}Box;

typedef struct DynObj
{
  int x, y, w, h;
  int type;
  bool solid;
  SDL_Texture *image;
  Box *box;
}DynObj;

typedef struct Bloc
{
  int x, y, w, h;
  int type;
  bool solid;
  SDL_Texture *image;
}Bloc;


typedef struct Game
{
  int wmap, hmap;
  int level;
  int nbDynObj;
  Screen *screen;
  SDL_Texture *ground;
  Input *input;
  Perso *perso;
  Bloc ***map;
  DynObj **mapObj;
  TTF_Font *font;
}Game;

#endif
