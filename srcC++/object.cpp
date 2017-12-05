#include "../includeC++/object.h"
#include "../includeC++/game.h"

using namespace std;

extern Game game;

Object::Object() : x(20), y(20), w(32), h(32), nbFrame(1), time_frame(0), frame_index(0)
{

}

Object::Object(int x2, int y2, int type2) : x(x2), y(y2), w(32), h(32), nbFrame(1), frame_index(0),
    time_frame(0), type(type2)
{
  string name;
  switch (type)
  {
    case GROUND :
      name = "../graphics/Dirt.png";
      solid = true;
      break;
    case GROUND_2 :
      name =  "../graphics/Dirt_2.png";
      solid = true;
      break;
    case EMPTY :
      solid = false;
      break;
  }
  image[0] = name;
}

void Object::draw(SDL_Renderer *renderer, ImagesBank *bank)
{
  if (type != EMPTY)
  {
      Uint32 time_Sdl = SDL_GetTicks();
      frame_index = (int)(SDL_GetTicks()/(time_frame*1000))%nbFrame;
      int dep_x = 0;
      int dep_y = 0;
      game.calculDep(dep_x, dep_y);
      drawImage(bank->getImage(image[frame_index]), x - dep_x, y - dep_y, renderer);
  }
}

void Object::setSolid(bool set)
{
  solid = set;
}

void Object::setActive(bool set)
{
  active = set;
}

int Object::getX() const
{
  return x;
}

int Object::getY() const
{
  return y;
}

int Object::getW() const
{
  return w;
}

int Object::getH() const
{
  return h;
}

int Object::getType() const
{
  return type;
}

int Object::getTimeFrame() const
{
  return time_frame;
}

int Object::getNbFrame() const
{
  return nbFrame;
}

int Object::getDeepImage() const
{
  return deepImage;
}

bool Object::getSolid() const
{
  return solid;
}

bool Object::getActive() const
{
  return active;
}

string Object::getImage() const
{
  return image[frame_index];
}


Object::~Object()
{

}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  return !(x1+w1<=x2 || x1>=x2+w2 || y1+h1<=y2 || y1>=y2+h2);
}

Object *collisionMap(bool solid, int x1, int y1, int w1, int h1)
{
  for (int i=0; i<game.getWMap() * game.getHMap(); i++)
  {
    if (game.getMap(i)->getSolid() == solid)
    {
      if (collision(x1, y1, w1, h1, game.getMap(i)->getX(), game.getMap(i)->getY(),
            game.getMap(i)->getW(), game.getMap(i)->getH()))
      {
        return game.getMap(i);
      }
    }
  }
  return 0;
}
