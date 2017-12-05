#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include "defs.h"
#include "entity.h"

class Game;

class Character : public Entity
{
  public :

  Character();

  //autres
  void update();
  void movement();
  void setInteract(bool set);

  //accesseurs
  bool getInteract() const;

  ~Character();

  protected :

  bool interact;
};


#endif
