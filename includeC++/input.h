#ifndef DEF_INPUT
#define DEF_INPUT

#include "defs.h"

class Game;

class Input
{
  public :

  Input();

  //autres
  void updateEvents();
  void manageInputs();
  void updateInputs();

  //accesseurs
  int getXCursor() const;
  int getYCursor() const;
  bool getQuit() const;
  bool getKey(int scancode) const;
  bool getKeyMouse(int button) const;

  ~Input();

  protected :

  int xCursor, yCursor;
  bool quit;
  bool key[SDL_NUM_SCANCODES];
  bool mouse[5];

};

#endif
