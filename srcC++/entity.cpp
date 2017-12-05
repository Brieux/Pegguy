#include "../includeC++/entity.h"
#include "../includeC++/game.h"

extern Game game;

using namespace std;

Entity::Entity() : hJump(10), jumpAct(0)
{

}


void Entity::manageHP(int nbHP)
{

}

void Entity::changeDirection(int direction)
{

}

void Entity::manageInvincible()
{

}

void Entity::setJump()
{
  if (collisionMap(true, x, y + 1, w, h) && !game.getInput()->getKey(SDL_SCANCODE_W))
  {
    jumpAct = 0;
  }
  else
  {
    if (!game.getInput()->getKey(SDL_SCANCODE_W))
    {
      jumpAct = hJump;
    }
  }
  if (collisionMap(true, x, y - 1, w, h))
  {
    jumpAct = hJump;
  }
}

void Entity::jump()
{
  if (jumpAct < hJump)
  {
    vSpeedAct = -vSpeed;
    jumpAct++;
  }
}

void Entity::changeHand()
{

}

void Entity::addEquipment()
{

}

void Entity::deleteEquipment()
{

}

//accesseurs
int Entity::getHP() const
{
  return hp;
}

int Entity::getDirection() const
{
  return direction;
}

int Entity::getWaitShoot() const
{
  return waitShoot;
}

int Entity::getHJump() const
{
  return hJump;
}

int Entity::getJumpAct() const
{
  return jumpAct;
}

int Entity::getInvincible() const
{
  return invincible;
}

std::vector<DynObj> Entity::getEquipment() const
{
  return equipment;
}

DynObj *Entity::getHand() const
{
  return hand;
}


Entity::~Entity()
{

}
