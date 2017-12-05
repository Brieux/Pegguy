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
  for (uint i=0; i<5; i++)
  {
    input->mouse[i] = false;
  }
  input->xCursor = 0;
  input->yCursor = 0;
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
      case SDL_MOUSEBUTTONDOWN:
        input->mouse[event.button.button] = true;
        break;
      case SDL_MOUSEBUTTONUP:
        input->mouse[event.button.button] = false;
        break;
      case SDL_MOUSEMOTION:
        input->xCursor = event.motion.x;
        input->yCursor = event.motion.y;

    }
  }
}

void updateInputs(Game *game)
{
  //quit
  if (game->input->key[SDL_SCANCODE_ESCAPE])
  {
    game->input->quit = true;
  }

  //deplacement droit
  if (game->input->key[SDL_SCANCODE_D])
  {
    if (!game->dialogue)
    {
      game->perso->direction = RIGHT;
      move(game, game->perso, game->perso->hSpeed, 0);
      game->perso->move = true;
      if (game->sin)
      {
        game->sin->direction = RIGHT;
        move(game, game->sin, game->sin->hSpeed, 0);
        game->perso->move = true;
      }
    }
  }

  //deplacement gauche
  else if (game->input->key[SDL_SCANCODE_A])
  {
    if (!game->dialogue)
    {
      game->perso->direction = LEFT;
      move(game, game->perso, -game->perso->hSpeed, 0);
      game->perso->move = true;
      if (game->sin)
      {
        game->sin->direction = LEFT;
        move(game, game->sin, -game->sin->hSpeed, 0);
        game->perso->move = true;
      }
    }
  }
  else
  {
    if (!game->input->key[SDL_SCANCODE_D])
    {
      game->perso->move = false;
      if (game->sin)
      {
        game->perso->move = false;
      }
    }
  }

  //interaction
  if (game->input->key[SDL_SCANCODE_UP])
  {
    if (game->dialogue)
    {
      gestionDialogues(game, CHOICE_PREVIOUS);
      game->input->key[SDL_SCANCODE_UP] = false;
    }
    else
    {
      if (game->perso->hand && (game->perso->hand->type == TRIANGLE ||
          game->perso->hand->type == CIRCLE || game->perso->hand->type == SQUARE))
      {
        game->perso->hand = NULL;
        game->perso->interact = false;
        game->input->key[SDL_SCANCODE_UP] = false;
      }
      else
      {
        game->perso->interact = true;
      }
    }
  }
  else
  {
    game->perso->interact = false;
  }
  if (game->input->key[SDL_SCANCODE_DOWN])
  {
    if (game->dialogue)
    {
      gestionDialogues(game, CHOICE_NEXT);
      game->input->key[SDL_SCANCODE_DOWN] = false;
    }
  }

  //tir
  if (game->input->key[SDL_SCANCODE_LEFT])
  {
    if (!game->dialogue)
    {
      if (game->perso->hand && game->perso->hand->type == DUMMY_LAUNCHER)
      {
        shoot(game);
      }
      game->input->key[SDL_SCANCODE_LEFT] = false;
    }
  }

  if (game->input->key[SDL_SCANCODE_RIGHT])
  {
    if (game->dialogue)
    {
      gestionDialogues(game, NEXT);
      game->input->key[SDL_SCANCODE_RIGHT] = false;
    }
  }

  //saut
  if (game->input->key[SDL_SCANCODE_W])
  {
    if (!game->dialogue)
    {
      if (game->perso->hJumpAct < game->perso->hJump)//si le perso n'a pas dépassé
      {                                                //la hauteur de saut max
        jump(game->perso);
      }
      else
      {
        game->input->key[SDL_SCANCODE_W] = false;
      }
      if (game->sin)
      {
        if (game->sin->hJumpAct < game->sin->hJump)//si le perso n'a pas dépassé
        {                                                //la hauteur de saut max
          jumpSin(game->sin);
        }
      }
    }
  }
  else
  {
    if (!collisionMap(game, game->perso->x, game->perso->y + 1,//si la touche de saut n'est pas
        game->perso->w, game->perso->h))                        //appuyée et que le perso est
    {                                                           //dans le vide,
      game->perso->hJumpAct = game->perso->hJump; /*on l'empeche de sauter de nouveau*/
    }
    if (game->sin)
    {
      if (!collisionMap(game, game->sin->x, game->sin->y + 1,//si la touche de saut n'est pas
          game->sin->w, game->sin->h))                        //appuyée et que le perso est
      {                                                           //dans le vide,
        game->sin->hJumpAct = game->sin->hJump; /*on l'empeche de sauter de nouveau*/
      }
    }
  }

  if (game->input->key[SDL_SCANCODE_1])
  {
    game->input->key[SDL_SCANCODE_1] = false;
    if (game->perso->sizeEquip > 0)
    {
      game->perso->hand = game->perso->equip[0];
    }
  }
}
