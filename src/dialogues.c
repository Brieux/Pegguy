#include "../include/dialogues.h"

void interactionNPC(Game *game)
{
  DynObj *npc = NULL;
  if ((npc = collisionMapObjNoSolid(game, game->perso->x, game->perso->y,
                game->perso->w, game->perso->h, 0)) && npc->type == NPC1 && game->perso->interact)
  {
    npc->dialogue = true;
    game->numDialogue = 1;
    game->dialogue = true;
    //npc->count = 50;
  }
}

void drawDialogueNPCs(Game *game, int dep_x, int dep_y)
//Fonction pour dessiner les dialogues des pnj
{
  for (int i=0; i<game->nbDynObj; i++)
  {
    if (game->mapObj[i]->type == NPC1 && game->mapObj[i]->dialogue /*count>0*/)
    {
        //Count est le temps d'affichage du dialogue
        //game->mapObj[i]->count--;
        /*print_line(game, game->mapObj[i]->x-50-dep_x, game->mapObj[i]->y-40-dep_y,
                  game->mapObj[i]->content);*/

        if (!game->dialogue)
        {
          game->mapObj[i]->dialogue = false;
        }
        else
        {
          dialogue(game, game->mapObj[i]->content, game->mapObj[i]->x-70-dep_x, game->mapObj[i]->y-100-dep_y);
        }
    }
  }
}

void gestionDialogues(Game *game, int type)
{
  switch (type)
  {
    case NEXT:
      if (game->endDialogue)
      {
        game->numDialogue = 0;
        game->endDialogue = false;
        game->dialogue = false;
      }
      else
      {
        game->choice = 0;
        game->numDialogue++;
      }
      break;
    case CHOICE_NEXT:
      if (game->nbChoices)
      {
        game->choice++;
        if (game->choice >= game->nbChoices)
        {
          game->choice = 0;
        }
      }
      break;

    case CHOICE_PREVIOUS:
      if (game->nbChoices)
      {
        game->choice--;
        if (game->choice < 0)
        {
          game->choice = game->nbChoices - 1;
        }
      }
      break;
  }
}

void dialogue(Game *game, char *text, int dep_x, int dep_y)
{
  if (game->numDialogue > 0)
  {
    char line[50];
    char choice[50];
    char *choice_1;
    char *choice_2;
    char *choice_3;
    int i = 0, k, n;
    for (int j=0; j<game->numDialogue; j++) //on va chercher le morceau de dialogue
    {                                      //correspondant au num où s'était arrêté
      k = 0;                              //le joueur
      while (text[i] != '\n' && text[i] != '\0' && text[i] != '\\')
      {                                 //on ecrit dans line tant qu'on ne tombe pas
        line[k] = text[i];              //sur '\n' (une demande d'interaction),
        k++;                          //sur '\0' (fin du dialogue),
        i++;                          //et sur '\\' (une demande de choix)
      }
      if (text[i] == '\0')            //si fin dialogue
      {
        game->endDialogue = true;     //on quitte
      }
      else if (text[i] == '\n')       //si demande interaction
      {
        i++;                          //on continue
      }
      else if (text[i] == '\\')       //si choix
      {
        i++;
        game->nbChoices = text[i] - 48; //le chiffre après '\\' indique le nombre de choix
        i++;
        for (int m=0; m<game->nbChoices; m++)  //on va ecrire dans chaque choix
        {                                     //le choix en question
          n = 0;
          while (text[i] != '\n' && text[i] != '\\' && text[i] != '\0')
          {
            choice[n] = text[i];
            n++;
            i++;
          }
          if (text[i] == '\0')
          {
            game->endDialogue = true;
          }
          i++;
          choice[n] = '\0';
          if (j == game->numDialogue - 1)  //si la demande de choix est bien celle
          {                               //où s'est arrêté le joueur
            drawImage(getImage(game, game->menuPointer), dep_x - 10,
                            dep_y + 30 + game->choice*20,
                            game->screen->pRenderer); //on dessine le pointeur
            switch (m)
            {
              case 0:     //et on affiche les choix
                choice_1 = choice;
                print_line(game, dep_x + 20, dep_y + 30, choice_1);
                break;
              case 1:
                choice_2 = choice;
                print_line(game, dep_x + 20, dep_y + 50, choice_2);
                break;
              case 2:
                choice_3 = choice;
                print_line(game, dep_x + 20, dep_y + 70, choice_3);
                break;
            }
          }
        }
      }
    }
    line[k] = '\0';
    print_line(game, dep_x, dep_y, line);
  }
}
