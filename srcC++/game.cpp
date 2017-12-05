#include "../includeC++/game.h"

using namespace std;

Game::Game()
{
  character = new Character();
  input = new Input();
  screen = new Screen();
  bank = new ImagesBank(screen->getRenderer());
  loadMap(1);

}

void Game::play()
{
  while (!input->getQuit())
  {
    updateGame();
    drawGame();
  }
}

void Game::calculDep(int &dep_x, int &dep_y){
    if (character->getX() > WINDOW_W/2){
        if (character->getX() > wMap * 32 - WINDOW_W/2){
            dep_x = wMap * 32 - WINDOW_W;
        } else {
            dep_x = character->getX() - WINDOW_W/2;
        }
    } else {
        dep_x = 0;
    }

    if (character->getY() > WINDOW_H/2){
        dep_y = character->getY() - WINDOW_H/2;
    } else {
        dep_y = 0;
    }
}

void Game::drawGame()
{
  screen->clearScreen();
  drawMap();
  drawCharacter();
  SDL_RenderPresent(screen->getRenderer());
}

void Game::drawCharacter()
{
  character->draw(screen->getRenderer(), bank);
}

void Game::drawMap()
{
  for (int i=0; i<map.size(); i++)
  {
    map[i]->draw(screen->getRenderer(), bank);
  }
}

void Game::updateGame()
{
  character->update();
  input->updateInputs();
}

void Game::loadMap(int level)
{
  FILE *file = fopen("../texts/level1.txt", "r");
  if (!file)
  {
    cout << "Unable to open level1.txt" << endl;
    exit(EXIT_FAILURE);
  }
  //on cherche le niveau correspondant
  int lvl_actu=0;
  while (lvl_actu!=level)
  {
    fscanf(file, "Lvl:%d", &lvl_actu);
    //tan qu'on ne trouve pas on saute une ligne
    if (jumpLine(file)==-1)
    {
      cout << "Unable to find level " << level << endl;
      exit(EXIT_FAILURE);
    }
  }

  fscanf(file, "x:%d y:%d", &wMap, &hMap);//on recupere la taille de la grille
  jumpLine(file);//puis on passe à la ligne suivante
  jumpLine(file);
  jumpLine(file);

  int xLink, yLink, type;
  for (int y=0; y<hMap; y++)
  {
    for (int x=0; x<wMap; x++)
    {
      type = fgetc(file);
      fscanf(file, ",x:%dy:%d/", &xLink, &yLink);
      switch (type)
      {
        case GROUND :
          map.push_back(new Object(x*32, y*32, type));
          break;
        case GROUND_2 :
          map.push_back(new Object(x*32, y*32, type));
          break;
        default :
          map.push_back(new Object(x*32, y*32, EMPTY));
          break;
      }
    }
    jumpLine(file);
  }
}

int Game::jumpLine(FILE *file)
{
  char caractere;
  while ((caractere=fgetc(file))!='\n')
  {
    if (caractere==EOF)
    {
      return -1;
    }
  }
  return 1;
}

//accesseurs
int Game::getWMap() const
{
  return wMap;
}

int Game::getHMap() const
{
  return hMap;
}

int Game::getLevel() const
{
  return level;
}

int Game::getNbBackground() const
{
  return nbBackground;
}

Object *Game::getBackground(int num) const
{
  return background[num];
}

Input *Game::getInput() const
{
  return input;
}

Character *Game::getCharacter() const
{
  return character;
}

Screen *Game::getScreen() const
{
  return screen;
}

Object *Game::getMap(int i) const
{
  return map[i];
}

Bullet *Game::getBullets(int num) const
{
  return bullets[num];
}


Game::~Game()
{

}
