#ifndef DEF_ENTITY
#define DEF_ENTITY

#include "defs.h"
#include "dynObj.h"

class Game;

class Entity : public DynObj
{
  public :

  Entity();

  //autres
  void manageHP(int nbHP);
  void changeDirection(int direction);
  void manageInvincible();
  void jump();
  void changeHand();
  void setJump();
  void addEquipment();
  void deleteEquipment();

  //accesseurs
  int getHP() const;
  int getDirection() const;
  int getWaitShoot() const;
  int getHJump() const;
  int getJumpAct() const;
  int getInvincible() const;
  std::vector<DynObj> getEquipment() const;
  DynObj *getHand() const;

  ~Entity();

  protected :

  int hp;
  int direction;
  int waitShoot;
  int hJump, jumpAct;
  bool invincible;
  std::vector<DynObj> equipment;
  DynObj *hand;
};

#endif
