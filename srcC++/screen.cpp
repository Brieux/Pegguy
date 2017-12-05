#include "../includeC++/screen.h"

using namespace std;

Screen::Screen()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow("Peggy", SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           WINDOW_W, WINDOW_H,
                                           SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    exit(EXIT_FAILURE);
  }

  //on cree le renderer de la fenetre
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
  {
    exit(EXIT_FAILURE);
  }

  //on initialise sdl2_image
  if (!IMG_Init(IMG_INIT_JPG))
  {
    exit(EXIT_FAILURE);
  }

  //on cache le curseur
  SDL_ShowCursor(SDL_DISABLE);
}

void Screen::clearScreen()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

//accesseurs
SDL_Window *Screen::getWindow() const
{
  return window;
}

SDL_Renderer *Screen::getRenderer() const
{
  return renderer;
}

Screen::~Screen()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  TTF_Quit();
}

void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *renderer)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture *loadTexture(char *image, SDL_Renderer *renderer)
{
  SDL_Surface *surface = IMG_Load(image);//on charge la surface
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);// puis la texture correspondante
  SDL_FreeSurface(surface);

  return texture;
}
