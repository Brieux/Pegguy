#ifndef DEF_IMAGESBANK
#define DEF_IMAGESBANK

#include "defs.h"
#include "screen.h"

#define BANK_SIZE 100

class ImagesBank
{
  public :

  ImagesBank();
  ImagesBank(SDL_Renderer *renderer);

  //autres
  int hash(std::string name);
  void place(char *name, SDL_Renderer *renderer);
  int search(std::string name);
  void printBank() const;

  //accesseurs
  SDL_Texture *getImage(std::string name);

  ~ImagesBank();

  protected :

  SDL_Texture *bank[BANK_SIZE];
  std::string bankName[BANK_SIZE];

};

#endif
