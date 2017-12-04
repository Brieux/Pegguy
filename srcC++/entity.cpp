#include "../includeC++/entity.h"

using namespace std;

Entity::Entity()
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

void Entity::jump()
{

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

int Entity::getSJump() const
{
  return sJump;
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
