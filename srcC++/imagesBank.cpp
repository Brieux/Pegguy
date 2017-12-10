#include "../includeC++/imagesBank.h"

using namespace std;

ImagesBank::ImagesBank()
{

}

ImagesBank::ImagesBank(SDL_Renderer *renderer)
{
  for (int i=0; i<BANK_SIZE; i++)
  {
    bank[i] = NULL;
    bankName[i] = "";
  }

  place("../graphics/door.png", renderer);
  place("../graphics/baby.png", renderer);
  place("../graphics/Dirt.png", renderer);
  place("../graphics/Dirt_2.png", renderer);
  place("../graphics/target.png", renderer);
  place("../graphics/box_destroyable.png", renderer);
  place("../graphics/box.png", renderer);
  place("../../blob.png", renderer);
  place("../../perso.png", renderer);
  place("../../sentryBlob.png", renderer);
  place("../../soldier.png", renderer);
}

//autres
int ImagesBank::hash(string name)
{
  const char *nameTab = name.c_str();
  int key = 0;
  for (int i=0; i<name.size(); i++)
  {
    key += nameTab[i] * pow(2, name.size()-i+1);
  }
  key %= BANK_SIZE;

  return key;
}

void ImagesBank::place(char *name, SDL_Renderer *renderer)
{
  int key = hash(name);
  int keyOrigine = key;
  while (bank[key] != NULL)
  {
    key++;
    if (key == keyOrigine)
    {
      cout << "No place for image " << name <<  endl;
      exit(EXIT_FAILURE);
    }
  }

  bank[key] = loadTexture(name, renderer);
  bankName[key] = name;
}

int ImagesBank::search(string name)
{
  int key = hash(name);
  int keyOrigine = key;
  while (bankName[key] != name)
  {
    key++;
    if (key == keyOrigine)
    {
      cout << "Image " << name << " not found" << endl;
      exit(EXIT_FAILURE);
    }
  }

  return key;
}

//accesseurs
SDL_Texture *ImagesBank::getImage(string name)
{
  int key = search(name);
  return bank[key];
}

void ImagesBank::printBank() const
{
  for (int i=0; i<BANK_SIZE; i++)
  {
    cout << bankName[i] << endl;
  }
}

ImagesBank::~ImagesBank()
{

}
