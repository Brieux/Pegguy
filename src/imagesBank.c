#include "../include/imagesBank.h"

void loadImagesBank(Game *game)
{
  game->imagesBank = malloc(sizeof(ImagesBank));
  if (!game->imagesBank){
    error("Unable to malloc imagesBank");
  }
  game->imagesBank->bank = malloc(BANK_SIZE * sizeof(SDL_Texture*));
  if (!game->imagesBank->bank){
    error("Unable to malloc imagesBank->bank");
  }
  game->imagesBank->bankName = malloc(BANK_SIZE * sizeof(char*));
  if (!game->imagesBank->bankName){
    error("Unable to malloc imagesBank->bankName");
  }
  for (int i=0; i<BANK_SIZE; i++)
  {
    game->imagesBank->bank[i] = NULL;
    game->imagesBank->bankName[i] = "";
  }

  placeBank("../graphics/door.png", game);
  placeBank("../graphics/baby.png", game);
  placeBank("../graphics/Dirt.png", game);
  placeBank("../graphics/Dirt_2.png", game);
  placeBank("../graphics/target.png", game);

  placeBank("../graphics/B_1.png", game);
  placeBank("../graphics/baby_2.png", game);
  placeBank("../graphics/background.png", game);
  placeBank("../graphics/billefinale.png", game);
  placeBank("../graphics/box_destroyable_ball.png", game);
  placeBank("../graphics/box_destroyable_dummy.png", game);
  placeBank("../graphics/box_destroyable.png", game);
  placeBank("../graphics/box.png", game);

  placeBank("../graphics/circle_base.png", game);
  placeBank("../graphics/circle_complete.png", game);
  placeBank("../graphics/circle.png", game);
  placeBank("../graphics/triangle_base.png", game);
  placeBank("../graphics/triangle_complete.png", game);
  placeBank("../graphics/triangle.png", game);
  placeBank("../graphics/square_base.png", game);
  placeBank("../graphics/square_complete.png", game);
  placeBank("../graphics/square.png", game);

  placeBank("../graphics/ghost.png", game);
  placeBank("../graphics/ghost_2.png", game);
  placeBank("../graphics/ghost_3.png", game);
  placeBank("../graphics/ghost_4.png", game);
  placeBank("../graphics/grid.png", game);
  placeBank("../graphics/Heart.png", game);
  placeBank("../graphics/link.png", game);
  placeBank("../graphics/menu_pointer.png", game);

  placeBank("../graphics/mobile_platform_horizontale.png", game);
  placeBank("../graphics/mobile_platform.png", game);
  placeBank("../graphics/mobile_platform_verticale.png", game);
  placeBank("../graphics/npc2.png", game);
  placeBank("../graphics/npc.png", game);
  placeBank("../graphics/piecefinale.png", game);
  placeBank("../graphics/secret_ground.png", game);
  placeBank("../graphics/menu_pointer.png", game);

  placeBank("../graphics/dummy_launcher/dummydownleft.png", game);
  placeBank("../graphics/dummy_launcher/dummydownright.png", game);
  placeBank("../graphics/dummy_launcher/dummy_launcher_handleftpointed.png", game);
  placeBank("../graphics/dummy_launcher/dummy_launcher_handrightpointed.png", game);
  placeBank("../graphics/dummy_launcher/dummy_launcher.png", game);
  placeBank("../graphics/dummy_launcher/dummy.png", game);
  placeBank("../graphics/dummy_launcher/dummyupleft.png", game);
  placeBank("../graphics/dummy_launcher/dummyupright.png", game);

  placeBank("../graphics/ghost_gun/ghost_gunleftpointed.png", game);
  placeBank("../graphics/ghost_gun/ghost_gunrightpointed.png", game);
  placeBank("../graphics/ghost_gun/ghost_gunleftpointed.png", game);
  placeBank("../graphics/ghost_gun/ghost_gun.png", game);
  placeBank("../graphics/ghost_gun/plasma.png", game);
  placeBank("../graphics/ghost_gun/ghost-gun-visualisation.png", game);

  placeBank("../graphics/boken.png", game);
  placeBank("../graphics/boken_left.png", game);
  placeBank("../graphics/hit_boken.png", game);
  placeBank("../graphics/hit_boken_left.png", game);
  placeBank("../graphics/box_destroyable_boken.png", game);

  placeBank("../graphics/spritepegguy/testprofildroitjambedroite.png", game);
  placeBank("../graphics/spritepegguy/testprofildroitjambegauche.png", game);
  placeBank("../graphics/spritepegguy/testprofilgauchejambedroite.png", game);
  placeBank("../graphics/spritepegguy/testprofilgauchejambegauche.png", game);
  placeBank("../graphics/spritepegguy/testprofilgauche.png", game);
  placeBank("../graphics/spritepegguy/testprofildroite.png", game);
  placeBank("../graphics/spritepegguy/jumpprofildroit.png", game);
  placeBank("../graphics/spritepegguy/jumpprofilgauche.png", game);

  placeBank("../graphics/bridge.png", game);

  //printBank(game);
}

//autres
int hash(ImagesBank *bank, char *name)
{
  int size = 0;
  for (size = 0; name[size] != '\0'; size++)//on récupère la taille de la chaîne
  {
  }
  int key = 0;
  for (int i= size - 15; i<size; i++)
  {
    key += name[i] * pow(2, size-i+1);//algo de hachage
  }
  key %= BANK_SIZE;
  return key;
}

void placeBank(char *name, Game *game)
{
  int key = hash(game->imagesBank, name);//on prend la clé de base
  int keyOrigine = key;
  while (game->imagesBank->bank[key] != NULL)
  {                                   //et on va chercher une place libre
    key++;                      //à partir de la clé originelle
    if (key >= BANK_SIZE)
    {
      key = 0;
    }
    if (key == keyOrigine)//si on retombe sur la clé de base, c'est que l'images
    {                     //n'existait pas
      fprintf(stderr, "No place for image %s\n", name);
      exit(EXIT_FAILURE);
    }
  }

  game->imagesBank->bank[key] = loadTexture(name, game->screen->pRenderer);
  game->imagesBank->bankName[key] = name;
}

int searchBank(Game *game, char *name)
{
  int key = hash(game->imagesBank, name);//hash originel
  int keyOrigine = key;

  while (strcmp(game->imagesBank->bankName[key], name) != 0)
  {                         //on cherche l'image
    key++;
    if (key >= BANK_SIZE)
    {
      key = 0;
    }
    if (key == keyOrigine || game->imagesBank->bank[key] == NULL)
    {                       //image non trouvée
      fprintf(stderr, "Image %s not found\n", name);
      exit(EXIT_FAILURE);
    }
  }

  return key;
}

SDL_Texture *getImage(Game *game, char *name)
{                               //on cherche l'image
  int key = searchBank(game, name);
  return game->imagesBank->bank[key];
}

void printBank(Game *game)//fonction utile uniquement aux devs
{
  int sum = 0;
  for (int i=0; i<BANK_SIZE; i++)
  {
    if (game->imagesBank->bank[i] != NULL)
    {
      printf("%d:%s\n", i, game->imagesBank->bankName[i]);
      sum++;
    }
  }
  printf("%d\n\n", sum);
}

void freeImagesBank(Game *game)
{
  for (int i=0; i<BANK_SIZE; i++)//on supprime toutes les images de la banque
  {
    if (game->imagesBank->bank[i])
    {
      SDL_DestroyTexture(game->imagesBank->bank[i]);
    }
  }
  free(game->imagesBank->bank);
  free(game->imagesBank->bankName);
}
