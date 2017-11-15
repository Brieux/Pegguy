#include "../include/defs.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));
  Game *game = loadGame();

  while (!game->input->quit)//boucle principale
  {
    inputs(game);
    drawGame(game);

  }

  quitSDL(game->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
