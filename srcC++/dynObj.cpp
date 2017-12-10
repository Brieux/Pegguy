#include "../includeC++/dynObj.h"
#include "../includeC++/game.h"

using namespace std;

extern Game game;

DynObj::DynObj() : hSpeed(5), vSpeed(15), hSpeedAct(0), vSpeedAct(0), gravite(true)
{

}

DynObj::DynObj(int x2, int y2, int type2) : Object(x2, y2, type2), hSpeed(5),
    vSpeed(15), hSpeedAct(0), vSpeedAct(0), gravite(true)
{
  string name;
  switch (type)
  {
    case BOX_DESTROYABLE_EMPTY :
      name = "../../sentryBlob.png";
      solid = true;
      w = 64;
      y-=32;
      h = 96;
      subType = BOX;
      break;
    case BOX :
      name =  "../../blob.png";
      solid = true;
      w = 64;
      y-=32;
      h = 96;
      subType = BOX;
      break;
    case BOX_DESTROYABLE_BALL :
      name =  "../../soldier.png";;
      solid = true;
      w = 64;
      h = 64;
      subType = BOX;
      break;
    case BOX_DESTROYABLE_DUMMY_LAUNCHER :
      name =  "../../soldier.png";
      solid = true;
      w = 64;
      h = 64;
      subType = BOX;
      break;
  }
  image[0] = name;
}

void DynObj::update()
{
  movement();
}

void DynObj::movement()
{
  applyGravite();
  for (int i=0; i<abs(hSpeedAct); i++)
  {
    cout << type << " " << x << " " << y << endl;
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

void DynObj::move(int direction, int hSpeed2, int vSpeed2)
{
  switch (direction)
  {
    case LEFT :
      cout << type << " " << x << " " << y << " " << hSpeedAct <<  endl;
      hSpeedAct = -hSpeed2;
      break;
    case RIGHT :
      hSpeedAct = hSpeed2;
      break;
  }
}

void DynObj::applyGravite()
{
  if (gravite)
  {
    vSpeedAct += GRAVITE;
    if (vSpeedAct > S_DOWN)
    {
      vSpeedAct = S_DOWN;
    }
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
