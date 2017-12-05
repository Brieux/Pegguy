#ifndef DEF_DEFS
#define DEF_DEFS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

enum {EMPTY=48/*0*/, GROUND/*1*/, GROUND_2/*2*/, BOX_DESTROYABLE_EMPTY/*3*/, BALL/*4*/,
      BOX/*5*/, DUMMY_LAUNCHER/*6*/, DUMMY/*7*/, TARGET/*8*/, DOOR/*9*/,
      BOX_DESTROYABLE_BALL=65/*A*/, BOX_DESTROYABLE_DUMMY_LAUNCHER/*B*/, NPC1/*C*/,
      SQUARE/*D*/, CIRCLE/*E*/, TRIANGLE/*F*/, SQUARE_BASE/*G*/, CIRCLE_BASE/*H*/,
      TRIANGLE_BASE/*I*/, MOBILE_PLATFORM=75/*K*/, SECRET_GROUND};


enum {OBJECT};

enum {LEFT, RIGHT, UP, DOWN};

#define WINDOW_W 1280
#define WINDOW_H 640
#define GRAVITE 2
#define S_DOWN 18

#endif
