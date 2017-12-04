#include "../includeC++/dynObj.h"
#include "../includeC++/game.h"

using namespace std;

extern Game game;

DynObj::DynObj() : hSpeed(5), vSpeed(5), hSpeedAct(0), vSpeedAct(0)
{

}

void DynObj::update()
{
  movement();
}

void DynObj::movement()
{
  for (int i=0; i<abs(hSpeedAct); i++)
  {
    if (!collisionMap(true, x + abs(hSpeedAct)/hSpeedAct, y, w, h))
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
}

void DynObj::move(int direction)
{
  switch (direction)
  {
    case LEFT :
      hSpeedAct = -hSpeed;
      break;
    case RIGHT :
      hSpeedAct = hSpeed;
      break;
  }

}

void DynObj::manageCounter(int nbCounter)
{

}

//accesseurs
int DynObj::getVSpeed() const
{
  return vSpeed;
}

int DynObj::getHSpeed() const
{
  return hSpeed;
}

int DynObj::getVSpeedAct() const
{
  return vSpeedAct;
}

int DynObj::getHSpeedAct() const
{
  return hSpeedAct;
}

bool DynObj::getGravite() const
{
  return gravite;
}

int DynObj::getXLink() const
{
  return xLink;
}

int DynObj::getYLink() const
{
  return yLink;
}

int DynObj::getCount() const
{
  return count;
}

bool DynObj::getIsMoved() const
{
  return isMoved;
}

bool DynObj::getLinked() const
{
  return linked;
}

DynObj *DynObj::getLink() const
{
  return link;
}

DynObj::~DynObj()
{

}
