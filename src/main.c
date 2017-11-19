#include "../include/defs.h"


int main(int argc, char *argv[])
{
  srand(time(NULL));

  int map_selected = 1;//selection du niveau en argument
  if (argc == 2){
  	  map_selected = atoi(argv[1]);
  }

  Game *game = loadGame(map_selected);

  while (!game->input->quit)//boucle principale
  {
    inputs(game);
    updateGame(game);
    drawGame(game);

  }

  quitSDL(game->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
