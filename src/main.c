#include "../include/defs.h"


int main(int argc, char *argv[])
{
  srand(time(NULL));

  int map_selected = 1;//selection du niveau en argument
  if (argc == 2){
  	  map_selected = atoi(argv[1]);
  }

  Game *game = loadGame(map_selected);

  game->first_mob = init_monster(game, NULL, B1, 15*32, 17*32);

  while (!game->input->quit)//boucle principale
  {
    inputs(game);
    updateGame(game);
    drawGame(game);
    mob_gestion(game);

  }

  freeAll(game);
  quitSDL(game->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
