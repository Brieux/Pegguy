#include "../include/sin.h"

void graviteSin(Game *game, Perso *perso)
{
    DynObj *dynObj = NULL;
    perso->vSpeed += -GRAVITE;
    if (perso->vSpeed < -VDOWN)
    {
      perso->vSpeed = -VDOWN;/*si la vitesse de chute a été dépassée, on la bloque*/
    }

    for (uint i=0; i<abs(perso->vSpeed); i++)
    {
      if (collisionMap(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          perso->w, perso->h) || //si collision avec element du decor
          collisionMapObj(game, perso->x, perso->y + abs(perso->vSpeed)/perso->vSpeed,
          perso->w, perso->h, 0))//si collision avec objet dynamique
      {
        perso->vSpeed = 0;
        perso->hJumpAct = perso->hJump;//on stoppe

        if (collisionMap(game, perso->x, perso->y - 1,
            perso->w, perso->h) ||
            (dynObj = collisionMapObj(game, perso->x, perso->y - 1,
            perso->w, perso->h, 0)))//si c'etait le sol
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

void jumpSin(Perso *perso)
{
  perso->vSpeed = perso->vJump;
  perso->hJumpAct++;
}

Perso *loadSin(Game *game)
{
  Perso *perso = malloc(sizeof(Perso));
  if (!perso){
    fprintf(stderr, "Unable to alloc perso in loadPerso\n");
    exit(EXIT_FAILURE);
  }
  perso->nb_frame = 4;

  perso->image = malloc(2 * sizeof(SDL_Texture*));
  perso->image[0] = malloc(perso->nb_frame * sizeof(SDL_Texture*));
  perso->image[1] = malloc(perso->nb_frame * sizeof(SDL_Texture*));

  if (!perso->image){
    fprintf(stderr, "Unable to alloc image in perso\n");
    exit(EXIT_FAILURE);
  }
  //Chargement des textures
  perso->image[0][0] = "../graphics/spritepegguy/testprofildroite.png";
  perso->image[0][1] = "../graphics/spritepegguy/testprofildroitjambedroite.png";
  perso->image[0][2] = perso->image[0][0];
  perso->image[0][3] = "../graphics/spritepegguy/testprofildroitjambegauche.png";

  perso->image[1][0] = "../graphics/spritepegguy/testprofilgauche.png";
  perso->image[1][1] = "../graphics/spritepegguy/testprofilgauchejambedroite.png";
  perso->image[1][2] = perso->image[1][0];
  perso->image[1][3] = "../graphics/spritepegguy/testprofilgauchejambegauche.png";

  //A changer selon les maps je suppose ?
  perso->w = 32;
  perso->h = 64;
  perso->x = 96;
  perso->y = 200;
  perso->waitShoot = 0;
  perso->direction = RIGHT;
  perso->move = false;
  perso->hSpeed = 5;
  perso->vSpeed = 0;
  perso->vJump = 13;
  perso->hJump = 13;
  perso->hJumpAct = 0;
  perso->interact = 0;
  perso->hand = NULL;
  perso->sizeEquip = 0;
  perso->equip = malloc(perso->sizeEquip*sizeof(DynObj*));
  perso->invincible = 0;
  perso->hp = 3;
  return perso;
}
