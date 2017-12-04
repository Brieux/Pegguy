#include "../includeC++/input.h"
#include "../includeC++/game.h"

using namespace std;

extern Game game;

Input::Input()
{
  quit = false;
  for (uint i=0; i<SDL_NUM_SCANCODES; i++)
  {
    key[i] = false;
  }
  for (uint i=0; i<5; i++)
  {
    mouse[i] = false;
  }
  xCursor = 0;
  yCursor = 0;
}

//autres
void Input::updateEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        key[event.key.keysym.scancode] = true;
        break;
      case SDL_KEYUP:
        key[event.key.keysym.scancode] = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        mouse[event.button.button] = true;
        break;
      case SDL_MOUSEBUTTONUP:
        mouse[event.button.button] = false;
        break;
      case SDL_MOUSEMOTION:
        xCursor = event.motion.x;
        yCursor = event.motion.y;

    }
  }
}

void Input::manageInputs()
{
  //quit
  if (key[SDL_SCANCODE_ESCAPE])
  {
    quit = true;
  }

  if (key[SDL_SCANCODE_A])
  {
    game.getCharacter()->move(LEFT);
  }

  if (key[SDL_SCANCODE_D])
  {
    game.getCharacter()->move(RIGHT);
  }

}

void Input::updateInputs()
{
  updateEvents();
  manageInputs();
}

//accesseurs
int Input::getXCursor() const
{
  return xCursor;
}

int Input::getYCursor() const
{
  return yCursor;
}

bool Input::getQuit() const
{
  return quit;
}

bool Input::getKey(int scancode) const
{
  return key[scancode];
}

bool Input::getKeyMouse(int button) const
{
  return key[button];
}


Input::~Input()
{

}
