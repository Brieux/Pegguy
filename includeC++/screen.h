#ifndef DEF_SCREEN
#define DEF_SCREEN

#include "defs.h"

class Screen
{
  public :

  Screen();

  //autres
  void clearScreen();

  //accesseurs
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;


  ~Screen();

  protected :

  SDL_Window *window;
  SDL_Renderer *renderer;

};

void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *renderer);
SDL_Texture *loadTexture(char *image, SDL_Renderer *renderer);

#endif
