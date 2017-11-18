#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawMap(game);
  SDL_RenderPresent(game->screen->pRenderer);
}

//Affichage de ce que l'on voit à l'écran seulement

void drawMap(Game *game){
    int perso_x = game->perso->x;       //Juste plus pratique
    int perso_y = game->perso->y;
    int dep_x;                          //écart entre début map et perso
    int dep_y;
    static int save_dep;                //sauvegarde du déplacement X
    
    //DEP HORIZONTAL
    if (perso_x > game->wmap*32 - WINDOW_W/2){      //quand perso en fin de map
        dep_x = save_dep;                           //On utiliise la sauvegarde 
    } else if (perso_x > WINDOW_W/2){               //Début du scroll
        dep_x = perso_x - WINDOW_W/2;               //WINDOW_W/2 pour garder le perso au millieu
        save_dep = dep_x;                           //Sauvegarde du dep
    } else {
        dep_x = 0;
    }

    //DEP VERTICAL
    if (perso_y > WINDOW_H){
        dep_y = perso_y - WINDOW_H/2;
    } else {
        dep_y = 0;
    }

    //Les +1 dans les boucles sont pour afficher le début de laprocaine ligne à l'écran
    for (int x = 0; x < WINDOW_W/32 + 1; x++){
        if (x + dep_x/32>= game->wmap){         //Pour éviter les segfault à cause du +1
            break;
        }
        for (int y = 0; y < WINDOW_H/32 + 1; y++){
            if (y + dep_y/32>= game->hmap){     //Même "astuce"
                break;
            }
            switch (game->map[x + dep_x/32][y + dep_y/32]->type){
                case GROUND:
                    drawImage(game->map[x + dep_x/32][y + dep_y/32]->image,
                                x*32 - dep_x%32,
                                y*32 - dep_y%32,
                                game->screen->pRenderer
                    );
                  break;
            }
        }
    }
    drawImage(game->perso->image, perso_x-dep_x, perso_y-dep_y, game->screen->pRenderer);
    //printf(" Perso en %d:%d\n", perso_x, perso_y);

}

void clearScreen(Screen *screen)
{
  SDL_SetRenderDrawColor(screen->pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(screen->pRenderer);
}

void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *pRenderer)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(pRenderer, texture, NULL, &dest);
}
