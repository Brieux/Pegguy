#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef unsigned int uint;

enum {GROUND, EMPTY};

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
  bool jump;
  bool letal, solid;
  char *content;
  void *hand;
  SDL_Texture *image;
  void *equip[];

}Perso;

typedef struct Bloc
{
  int x, y, w, h;
  int type;
  SDL_Texture *image;
}Bloc;


typedef struct Game
{
  Screen *screen;
  SDL_Texture *ground;
  Input *input;
  Perso *perso;
  Bloc ***map;
  int wmap, hmap;
}Game;

#endif
