#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawMap(game);
  
  SDL_RenderPresent(game->screen->pRenderer);
}

//Affichage de ce que l'on voit à l'écran seulement

void drawMap(Game *game){
    int perso_x = game->perso->x;
    int dep_x; //Faudra gérer dep_y

    if (perso_x > game->wmap*32 - WINDOW_W/2){
        dep_x = game->wmap - WINDOW_W/32;
        
    } else if (perso_x > WINDOW_W/2){
        dep_x = perso_x - WINDOW_W/2;   //On affiche avec le perso au centre
    }
    else {
        dep_x = 0;
    }
    
    for (int x = 0; x < WINDOW_W/32 + 1; x++){      //ATTENTION AU +1 dangereux source de crash
        if (x >= game->wmap){
            break;
        }
        for (int y = 0; y < WINDOW_H/32; y++){
            switch (game->map[x + dep_x/32][y]->type){
                case GROUND:
                    drawImage(game->map[x + dep_x/32][y]->image, x*32 - dep_x%32, y*32, game->screen->pRenderer);
                  break;
            }
        }
    }
    drawImage(game->perso->image, game->perso->x - dep_x, game->perso->y, game->screen->pRenderer);
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
