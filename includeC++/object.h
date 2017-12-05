#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "defs.h"
#include "screen.h"
#include "imagesBank.h"

class Game;

class Object
{
  public :

  Object();
  Object(int x, int y, int type);

  //autres
  void draw(SDL_Renderer *renderer, ImagesBank *bank);
  void setSolid(bool set);
  void setActive(bool set);

  //accesseurs
  int getX() const;
  int getY() const;
  int getW() const;
  int getH() const;
  int getType() const;
  int getTimeFrame() const;
  int getNbFrame() const;
  int getDeepImage() const;
  bool getSolid() const;
  bool getActive() const;
  std::string getImage() const;

  ~Object();

  protected :

  int x, y, w, h;
  int type;
  int nbFrame;
  double time_frame;
  int frame_index;
  int deepImage;
  bool solid;
  bool active;
  std::string image[1];
};

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
Object *collisionMap(bool solid, int x1, int y1, int w1, int h1);

#endif
