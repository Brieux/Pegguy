#include "../include/defs.h"


int main(int argc, char *argv[])
{
  srand(time(NULL));

  int map_selected = 1;//selection du niveau en argument
  if (argc == 2){
  	  map_selected = atoi(argv[1]);
  }

  Game *game = loadGame(map_selected);

/*add_monster(game, B1, 15*32, 17*32);
add_monster(game, B1, 16*32, 18*32);*/



  add_monster(game, BEBE, 780, 300);


  while (!game->input->quit && game->perso->hp > 0)//boucle principale
  {
    inputs(game);
    updateGame(game);
    drawGame(game);
    mob_gestion(game); //Problème dans la gestion des mobs, plus précisement dans les collisions

  }
  if (game->perso->hp <= 0){
      printf("Perdu :D\n");
  }

  freeAll(game);
  freeImagesBank(game);
  quitSDL(game->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
