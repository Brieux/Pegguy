#include "../includeC++/character.h"
#include "../includeC++/game.h"

using namespace std;

Character::Character()
{
  x = 64;
  y = 200;
  w = 32;
  h = 64;
  hSpeed = 6;
  gravite = true;
  image[0] = "../../perso.png";
}

void Character::update()
{
  movement();
  setJump();
}

void Character::movement()
{
  Object *obj = NULL;
  applyGravite();
  for (int i=0; i<abs(hSpeedAct); i++)
  {
    if ((obj = collisionMap(true, x + abs(hSpeedAct)/hSpeedAct, y, w, h)))
    {
      if (obj->getSubType() == BOX)
      {
        DynObj *p_dynObj = (DynObj *)obj;
        x += abs(hSpeedAct)/hSpeedAct;
        if (hSpeedAct > 0)
        {
          p_dynObj->move(RIGHT, 1, 0);
        }
        else if (hSpeedAct < 0)
        {
          p_dynObj->move(LEFT, 1, 0);
        }
        hSpeedAct /= 2;
      }
      else
      {
        hSpeedAct = 0;
      }
    }
    else if (!obj)
    {
      x += abs(hSpeedAct)/hSpeedAct;
    }
    else
    {
      hSpeedAct = 0;
    }
  }
  for (int i=0; i<abs(vSpeedAct); i++)
  {
    if (!collisionMap(true, x, y + abs(vSpeedAct)/vSpeedAct, w, h))
    {
      y += abs(vSpeedAct)/vSpeedAct;
    }
    else
    {
      vSpeedAct = 0;
    }
  }
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
