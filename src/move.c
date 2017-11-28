#include "../include/move.h"

void updateGame(Game *game)
{
  gravite(game, game->perso);
  graviteObj(game);
  updateProjectilesPosition(game);
  updateLinks(game);
  updateHand(game);
  updateObj(game);
  interactionNPC(game);
  if (game->perso->waitShoot!=0)
  {
    game->perso->waitShoot--;
  }

}

void updateLinks(Game *game)
{
  for (int i=0; i<game->nbDynObj; i++)//gestion des liens, à mettre dans une fonction
  {                                   //quand on aura l'editeur
    if (game->mapObj[i]->linked)
    {
      switch (game->mapObj[i]->type)
      {
        case DOOR:
          if (game->mapObj[i]->count == 0)
            game->mapObj[i]->active = false;
          break;
      }
      if (game->mapObj[i]->type == TRIANGLE_BASE || game->mapObj[i]->type == CIRCLE_BASE ||
            game->mapObj[i]->type == SQUARE_BASE)
      {

        DynObj *dynObj = collisionMapObjNoSolid(game, game->mapObj[i]->x, game->mapObj[i]->y,
                          game->mapObj[i]->w, game->mapObj[i]->h, game->mapObj[i]);
        if (dynObj && dynObj->link == game->mapObj[i])
        {
          dynObj->active = false;
          switch (game->mapObj[i]->type)
          {
            case TRIANGLE_BASE :
              SDL_DestroyTexture(game->mapObj[i]->image);
              game->mapObj[i]->image = loadTexture("../graphics/triangle_complete.png", game->screen->pRenderer);
              break;
            case CIRCLE_BASE :
              SDL_DestroyTexture(game->mapObj[i]->image);
              game->mapObj[i]->image = loadTexture("../graphics/circle_complete.png", game->screen->pRenderer);
              break;
            case SQUARE_BASE :
              SDL_DestroyTexture(game->mapObj[i]->image);
              game->mapObj[i]->image = loadTexture("../graphics/square_complete.png", game->screen->pRenderer);
              break;
          }
          if (game->mapObj[i]->link)
          {
            game->mapObj[i]->link->count--;
          }
        }
      }
    }
  }
}

void updateBall(Game *game, DynObj *ball)
{
  if (ball->active &&
          collision(game->perso->x, game->perso->y, game->perso->w, game->perso->h,
                ball->x, ball->y, ball->w, ball->h))
  {
    ball->active = false;
    game->hud->nbBalls++;
  }
}

void updateDummyLauncher(Game *game, DynObj *dummyLauncher)
{
  if (dummyLauncher->active &&
          collision(game->perso->x, game->perso->y, game->perso->w, game->perso->h,
                dummyLauncher->x, dummyLauncher->y, dummyLauncher->w, dummyLauncher->h))
  {
    dummyLauncher->active = false;
    DynObj *dummyLauncher = initDynObj(game, DUMMY_LAUNCHER, 0, 0, 32, 32,
                                  false, true, false, 0, 0, "../graphics/dummy_launcher_hand.png");
    game->perso->hand = dummyLauncher; //on place le lance-tetine dans la main
    game->perso->sizeEquip++;
    game->perso->equip = realloc(game->perso->equip, game->perso->sizeEquip*sizeof(DynObj*));
    game->perso->equip[game->perso->sizeEquip-1] = dummyLauncher; //et dans l'inventaire
  }
}

void updateForms(Game *game, DynObj *form)
{
  if (form->active &&
          collision(game->perso->x, game->perso->y, game->perso->w, game->perso->h,
                form->x, form->y, form->w, form->h))
  {
    if ((form->type == TRIANGLE || form->type == CIRCLE ||
        form->type == SQUARE) && game->perso->interact)
    {
      game->perso->interact = false;
      game->input->key[SDL_SCANCODE_UP] = false;
      game->perso->hand = form;
    }
  }
}

void updateObj(Game *game)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    switch (game->mapObj[i]->type)
    {
      case BALL :
        updateBall(game, game->mapObj[i]);

        break;

      case DUMMY_LAUNCHER :
        updateDummyLauncher(game, game->mapObj[i]);
        break;
    }
    updateForms(game, game->mapObj[i]);
  }
}

void pickItems(Game *game)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->active &&
            collision(game->perso->x, game->perso->y, game->perso->w, game->perso->h,
                  game->mapObj[i]->x, game->mapObj[i]->y, game->mapObj[i]->w, game->mapObj[i]->h))
    {
      switch (game->mapObj[i]->type) //si collision avec bille
      {
        case BALL :
          game->mapObj[i]->active = false;
          game->hud->nbBalls++;
          break;
        case DUMMY_LAUNCHER : //si collision avec lance-tetine
          game->mapObj[i]->active = false;
          DynObj *dummyLauncher = initDynObj(game, DUMMY_LAUNCHER, 0, 0, 32, 32,
                                        false, true, false, 0, 0, "../graphics/dummy_launcher_hand.png");
          game->perso->hand = dummyLauncher; //on place le lance-tetine dans la main
          game->perso->sizeEquip++;
          game->perso->equip = realloc(game->perso->equip, game->perso->sizeEquip*sizeof(DynObj*));
          game->perso->equip[game->perso->sizeEquip-1] = dummyLauncher; //et dans l'inventaire
          break;
      }
      if ((game->mapObj[i]->type == TRIANGLE || game->mapObj[i]->type == CIRCLE ||
          game->mapObj[i]->type == SQUARE) && game->perso->interact)
      {
        game->perso->interact = false;
        game->input->key[SDL_SCANCODE_UP] = false;
        game->perso->hand = game->mapObj[i];
      }
    }
  }
}

void updateHand(Game *game)
{
  if (game->perso->hand)
  {
    if (game->perso->hand->type == TRIANGLE || game->perso->hand->type == CIRCLE ||
          game->perso->hand->type == SQUARE)
    {
      game->perso->hand->x = game->perso->x;
      game->perso->hand->y = game->perso->y - 32;
    }
    else
    {
      game->perso->hand->x = game->perso->x;
      game->perso->hand->y = game->perso->y;
    }
  }

}

void move(Game *game, int vx, int vy)
{
  int wPerso = game->perso->w;
  int hPerso = game->perso->h;
  DynObj *dynObj = NULL;

  for (uint i=0; i<abs(vx); i++)
  {
    if (!collisionMap(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso))
    {//si pas de decor solide
      if ((dynObj = collisionMapObj(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso, 0)) != 0)
      {//si collision avec objet dynamique
        if (dynObj->type == BOX || dynObj->type == BOX_DESTROYABLE_EMPTY ||
            dynObj->type == BOX_DESTROYABLE_BALL || dynObj->type == BOX_DESTROYABLE_DUMMY_LAUNCHER)
        {//si c'est une caisse
          if (!collisionMap(game, dynObj->x + abs(vx)/vx,dynObj->y, dynObj->w, dynObj->h) &&
              !collisionMapObj(game, dynObj->x + abs(vx)/vx,dynObj->y, dynObj->w, dynObj->h, dynObj) &&
              !collisionMapObj(game, game->perso->x + abs(vx)/vx, game->perso->y,
                game->perso->w, game->perso->h, dynObj) &&
              game->perso->interact && !i%2)
          {//si on peut la deplacer et que le perso interagit
            game->perso->x+=abs(vx)/vx;
            dynObj->x+=abs(vx)/vx;//on pousse
          }
        }
      }
      else
      {
        if ((dynObj = collisionMapObj(game, game->perso->x - abs(vx)/vx*2, game->perso->y, wPerso, hPerso, 0)) != 0 &&
             game->perso->interact)//si caisse derriere soi
        {
          if (dynObj->type == BOX || dynObj->type == BOX_DESTROYABLE_EMPTY ||
              dynObj->type == BOX_DESTROYABLE_BALL || dynObj->type == BOX_DESTROYABLE_DUMMY_LAUNCHER)
          {
            if (!collisionMap(game, dynObj->x + abs(vx)/vx, dynObj->y, dynObj->w, dynObj->h) &&
                !collisionMapObj(game, dynObj->x + abs(vx)/vx, dynObj->y, dynObj->w, dynObj->h, dynObj) && !i%2)
            {
              game->perso->x+=abs(vx)/vx;
              dynObj->x+=abs(vx)/vx;//on tire la caisse
            }
          }
        }
        else
        {
          game->perso->x+=abs(vx)/vx;/*si le pixel suivant est vide, on fait avancer le perso*/
        }
      }
    }
    else
    {
      i = abs(vx);
    }
  }
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  w1--, w2--, h1--, h2--;
  return !(x1+w1<x2 || x1>x2+w2 || y1+h1<y2 || y1>y2+h2);//collision rectangulaire basique
}

bool collisionMap(Game *game, int x1, int y1, int w1, int h1)
{
  for (int x=0; x<game->wmap; x++)
  {
    for (int y=0; y<game->hmap; y++)
    {
      if (game->map[x][y]->solid)/*on teste toutes les collisions solides des cases de la map*/
      {
        if (collision(x1, y1, w1, h1, game->map[x][y]->x, game->map[x][y]->y,
                                       game->map[x][y]->w, game->map[x][y]->h))
        {
          return true;
        }
      }
    }
  }
  return false;
}

DynObj *collisionMapObj(Game *game, int x1, int y1, int w1, int h1, DynObj *dynObj)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->active && game->mapObj[i]->solid)
    {     /*on teste toutes les collisions solides des objets dyn de la map*/
      if (collision(x1, y1, w1, h1, game->mapObj[i]->x, game->mapObj[i]->y,
                                     game->mapObj[i]->w, game->mapObj[i]->h))
      {
        if (game->mapObj[i] != dynObj)
        {
          return game->mapObj[i];
        }
      }
    }
  }
  return 0;
}

DynObj *collisionMapObjNoSolid(Game *game, int x1, int y1, int w1, int h1, DynObj *dynObj)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->active)
    {     /*on teste toutes les collisions non solides des objets dyn de la map*/
      if (collision(x1, y1, w1, h1, game->mapObj[i]->x, game->mapObj[i]->y,
                                     game->mapObj[i]->w, game->mapObj[i]->h))
      {
        if (game->mapObj[i] != dynObj)
        {
          return game->mapObj[i];
        }
      }
    }
  }
  return 0;
}

void graviteObj(Game *game)
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->gravite)
    {
      game->mapObj[i]->vSpeed += GRAVITE;
      if (game->mapObj[i]->vSpeed > VDOWN)
      {
        game->mapObj[i]->vSpeed = VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
      }
      for (uint k=0; k<abs(game->mapObj[i]->vSpeed); k++)
      {
        if (collisionMap(game, game->mapObj[i]->x, game->mapObj[i]->y + abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed,
            game->mapObj[i]->w, game->mapObj[i]->h) || //si collision avec element du decor
            collisionMapObj(game, game->mapObj[i]->x, game->mapObj[i]->y + abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed,
            game->mapObj[i]->w,game->mapObj[i]->h, game->mapObj[i]))//si collision avec objet dynamique
        {
          game->mapObj[i]->vSpeed = 0;
        }
        else
        {
          game->mapObj[i]->y += abs(game->mapObj[i]->vSpeed)/game->mapObj[i]->vSpeed;//sinon on modifie la position du perso
        }
      }
    }
  }
}

void gravite(Game *game, Perso *perso)
{
    DynObj *dynObj = NULL;
    perso->vSpeed += GRAVITE;
    if (perso->vSpeed > VDOWN)
    {
      perso->vSpeed = VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
    }

    for (uint i=0; i<abs(perso->vSpeed); i++)
    {
      if (collisionMap(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          game->perso->w, game->perso->h) || //si collision avec element du decor
          collisionMapObj(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          game->perso->w, game->perso->h, 0))//si collision avec objet dynamique
      {
        perso->vSpeed = 0;
        perso->hJumpAct = perso->hJump;//on stoppe

        if (collisionMap(game, perso->x, perso->y + 1,
            game->perso->w, game->perso->h) ||
            (dynObj = collisionMapObj(game, perso->x, perso->y + 1,
            game->perso->w, game->perso->h, 0)))//si c'etait le sol
        {
          perso->hJumpAct = 0;//on remet le compteur de saut à 0
          if (dynObj)
          {
            destroyBox(game, dynObj);
          }
        }
      }
      else
      {
        perso->y += abs(perso->vSpeed)/perso->vSpeed;//sinon on modifie la position du perso
      }
    }
}

void destroyBox(Game *game, DynObj *dynObj)
{
  int x = dynObj->x;
  int y = dynObj->y;
  switch (dynObj->type)
  {
    case BOX_DESTROYABLE_EMPTY :
      dynObj->active = false;
      break;
    case BOX_DESTROYABLE_BALL :
      freeDynObj(dynObj);
      dynObj = initDynObj(game, BALL, x+16, y+32, 32, 32,
                false, true, false, 0, 0, "../graphics/billefinale.png");
      break;
    case BOX_DESTROYABLE_DUMMY_LAUNCHER :
      freeDynObj(dynObj);
      dynObj = initDynObj(game, DUMMY_LAUNCHER, x+16, y+32, 32, 32,
                  false, true, false, 0, 0, "../graphics/dummy_launcher.png");

      break;
  }
}

void updateProjectilesPosition(Game *game){
    if (!game->projectiles){
        return;
    }

    Projectile *p_projectile = NULL;
    p_projectile = game->projectiles;
    do{
        if (p_projectile->dynObj->x < 0 || p_projectile->dynObj->x > game->wmap*32){
            if (p_projectile->dynObj->y < 100 || p_projectile->dynObj->y > game->hmap*32){
                deleteProjectile(game, p_projectile);
            }
        } else {
          if (p_projectile->dynObj->vSpeed >= VDOWN){
              p_projectile->dynObj->vSpeed = VDOWN;
          } else {
              p_projectile->dynObj->vSpeed += GRAVITE/2;
          }
          p_projectile->dynObj->x += p_projectile->dynObj->hSpeed;
          p_projectile->dynObj->y += p_projectile->dynObj->vSpeed;

          DynObj * dynObj;
          if ((dynObj = collisionMapObjNoSolid(game, p_projectile->dynObj->x, p_projectile->dynObj->y,
                        p_projectile->dynObj->w, p_projectile->dynObj->h, 0)) && dynObj->type == TARGET){
              dynObj->link->count--;
              dynObj->active = false;
              p_projectile = p_projectile->following;
          } else if (collisionMap(game, p_projectile->dynObj->x, p_projectile->dynObj->y,
                            p_projectile->dynObj->w, p_projectile->dynObj->h) ||
              (dynObj = collisionMapObj(game, p_projectile->dynObj->x, p_projectile->dynObj->y,
                            p_projectile->dynObj->w, p_projectile->dynObj->h, 0))){
              if (dynObj) {
                  destroyBox(game, dynObj);
              }
              deleteProjectile(game, p_projectile);
        }


      }
      if (p_projectile){
          p_projectile = p_projectile->following;
      }
    }while(p_projectile);
}

void jump(Perso *perso)
{
  perso->vSpeed = -perso->vJump;
  perso->hJumpAct++;
}
