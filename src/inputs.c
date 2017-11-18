#include "../include/inputs.h"

//Création de l'input
Input *generateInput()
{
  Input *input = malloc(sizeof(Input));
  if (!input){
    fprintf(stderr, "Unable to alloc input in generateInput\n");
    exit(EXIT_FAILURE);
  }
  //On met toute les touches en 'non appuyée'
  input->quit = false;
  for (uint i=0; i<SDL_NUM_SCANCODES; i++)
  {
    input->key[i] = false;
  }
  return input;
}

void inputs(Game *game)
{
  //On regarde quelle touche a été appuyée
  updateEvents(game->input);

  //on agit en conséquence
  updateInputs(game);
}

void updateEvents(Input *input)
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        input->quit = true;
        break;
      case SDL_KEYDOWN:
        input->key[event.key.keysym.scancode] = true;
        break;
      case SDL_KEYUP:
        input->key[event.key.keysym.scancode] = false;
        break;
    }
  }
}

void updateInputs(Game *game)
{
  if (game->input->key[SDL_SCANCODE_ESCAPE])
  {
    game->input->quit = true;
  }

  //deplacement droit
  if (game->input->key[SDL_SCANCODE_D])
  {
      move(game, game->perso->hSpeed, 0);
  }
  //deplacement gauche
  if (game->input->key[SDL_SCANCODE_A])
  {
    move(game, -game->perso->hSpeed, 0);
  }
  if (game->input->key[SDL_SCANCODE_LEFT])
  {
    game->perso->interact = true;
  }
  else
  {
    game->perso->interact = false;
  }
  //saut
  if (game->input->key[SDL_SCANCODE_W])
  {
    if (game->perso->hJumpAct < game->perso->hJump)//si le perso n'a pas dépassé
    {                                                //la hauteur de saut max
      jump(game->perso);
    }
    else
    {
      game->input->key[SDL_SCANCODE_W] = false;
    }
  }
  else
  {
    if (!collisionMap(game, game->perso->x, game->perso->y + 1,//si la touche de saut n'est pas
        game->perso->w, game->perso->h))                        //appuyée et que le perso est
    {                                                           //dans le vide,
      game->perso->hJumpAct = game->perso->hJump; /*on l'empeche de sauter de nouveau*/
    }
  }
}
