#ifndef DEF_GAME
#define DEF_GAME

#include "defs.h"
#include "object.h"
#include "character.h"
#include "input.h"
#include "bullet.h"
#include "screen.h"
#include "imagesBank.h"

class Game
{

  public :

  Game();
  //autres
  void play();
  void drawGame();
  void drawCharacter();
  void drawMap();
  void updateGame();
  void loadMap(int level);
  int jumpLine(FILE *file);
  void calculDep(int &dep_x, int &dep_y);

  //accesseurs
  int getWMap() const;
  int getHMap() const;
  int getLevel() const;
  int getNbBackground() const;
  Object *getBackground(int num) const;
  Input *getInput() const;
  Character *getCharacter() const;
  Screen *getScreen() const;
  Object *getMap(int i) const;
  Bullet *getBullets(int num) const;

  ~Game();

  protected :

  int wMap, hMap;
  int level;
  int nbBackground;
  Object **background;
  Input *input;
  Screen *screen;
  Character *character;
  ImagesBank *bank;
  std::vector<Object*> map;
  std::vector<Bullet*> bullets;
};

#endif
