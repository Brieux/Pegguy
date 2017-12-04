#include "../includeC++/character.h"
#include "../includeC++/game.h"

using namespace std;

Character::Character()
{
  x = 64;
  y = 200;
  w = 32;
  h = 32;
  image[0] = "../graphics/baby.png";
}

void Character::update()
{
  movement();
}

void Character::movement()
{
  DynObj::movement();
  hSpeedAct = 0;
}

void Character::setInteract(bool set)
{

}

bool Character::getInteract() const
{
  return interact;
}

Character::~Character()
{

}
