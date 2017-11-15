#include "../include/screen.h"

void error(char *cmd)
{
  fprintf(stderr, "%s %s\n", cmd, SDL_GetError());
  exit(EXIT_FAILURE);
}

Screen *initScreen(char *title)
{
  Screen *screen = malloc(sizeof(Screen));

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    error("Unable to initialize SDL:");
  }

  screen->pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           WINDOW_W, WINDOW_H,
                                           SDL_WINDOW_SHOWN);
  if (screen->pWindow == NULL)
  {
    error("Unable to initialize the window:");
  }

  screen->pRenderer = SDL_CreateRenderer(screen->pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
  if (screen->pRenderer == NULL)
  {
    error("Unable to initialize the renderer:");
  }

  if (!IMG_Init(IMG_INIT_JPG))
  {
    printf( "Unable to initialize SDL_image: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }


  SDL_ShowCursor(SDL_DISABLE);

  return screen;
}

void quitSDL(Screen *screen)
{
  SDL_DestroyRenderer(screen->pRenderer);
  SDL_DestroyWindow(screen->pWindow);
  IMG_Quit();
  SDL_Quit();
}
