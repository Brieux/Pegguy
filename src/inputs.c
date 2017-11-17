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
  //On regarde quelle touche à été appuyée
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
  if (game->input->key[SDL_SCANCODE_D])
  {
      move(game, &game->perso->x, &game->perso->y, game->perso->hSpeed, 0);
  }
  if (game->input->key[SDL_SCANCODE_A])
  {
    move(game, &game->perso->x, &game->perso->y, -game->perso->hSpeed, 0);
  }
  if (game->input->key[SDL_SCANCODE_LEFT])
  {

  }
  if (game->input->key[SDL_SCANCODE_W])
  {
    if (game->perso->hJumpAct < game->perso->hJump)
    {
      //jump(&game->perso);
    }
    else
    {
      game->input->key[SDL_SCANCODE_W] = false;
    }
  }
  else
  {
    /*if (!groundCollision(game->perso->y + game->perso->h + 1))
    {
      game->perso->hJumpAct = game->perso->hJump;
    }*/
  }
}
