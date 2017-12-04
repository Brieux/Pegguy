#ifndef DEF_DYNOBJ
#define DEF_DYNOBJ

#include "defs.h"
#include "object.h"

class Game;

class DynObj : public Object
{
  public :

  DynObj();

  //autres
  void update();
  void movement();
  void move(int direction);
  void manageCounter(int nbCounter);


  //accesseurs
  int getVSpeed() const;
  int getHSpeed() const;
  int getVSpeedAct() const;
  int getHSpeedAct() const;
  bool getGravite() const;
  int getXLink() const;
  int getYLink() const;
  int getCount() const;
  bool getIsMoved() const;
  bool getLinked() const;
  DynObj *getLink() const;

  ~DynObj();

  protected :

  int vSpeed, hSpeed, vSpeedAct, hSpeedAct;
  bool gravite, isMoved;
  bool linked;
  DynObj *link;
  int xLink, yLink;
  int count;
};


#endif
