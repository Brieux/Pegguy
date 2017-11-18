#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawMap(game);
  SDL_RenderPresent(game->screen->pRenderer);

  if (DEBUG){
      consol_d(game);
  }
}

//Affichage de ce que l'on voit à l'écran seulement

void drawMap(Game *game){
    int dep_x;  //Nombre de pixel à passer sur la gauche
    int dep_y;  //Nombre de pixel à passer sur le haut

    if (game->perso->x > WINDOW_W/2){
        if (game->perso->x > game->wmap * 32 - WINDOW_W/2){
            dep_x = game->wmap * 32 - WINDOW_W;
        } else {
            dep_x = game->perso->x - WINDOW_W/2;
        }
    } else {
        dep_x = 0;
    }

    if (game->perso->y + game->perso->h > WINDOW_H){
        dep_y = game->perso->y + game->perso->h - WINDOW_H * 0.9;
        //0.9 est un coefficient qu'on peut modifier de 0.1 à 1
        //Plus il est bas, plus on peut voir en dessous du personnage.
    } else {
        dep_y = 0;
    }

    for (int x = 0; x < WINDOW_W/32 + 1; x++){
        if (x + dep_x/32 >= game->wmap || x + dep_x/32 < 0)    break;
        for (int y = 0; y < WINDOW_H/32 + 1; y++){
            if (y + dep_y/32>= game->hmap)    break;
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
    /*
    *   Faudra afficer tous les objets dans cette fonction,
    *   ou alors renvoyer les valeurs de dep_x et dep_y
    *   et n'afficher que si c'est sur l'écran actuel
    */
    int frame_index = 0;
    if (game->perso->vSpeed !=0){
        frame_index = game->perso->nb_frame - 1;
    } else {
        frame_index = abs((game->perso->x/20)%(game->perso->nb_frame-1));
    }
    drawImage(game->perso->image[frame_index],
                game->perso->x - dep_x,
                game->perso->y-dep_y,
                game->screen->pRenderer
    );
}

void consol_d(Game *game){
    char debug_text[256];
    sprintf(debug_text, "%d %d\n", game->perso->x, game->perso->y);
    SDL_Color color_text = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(game->font, debug_text, color_text);
    if (!text_surface){
        fprintf(stderr, "consol_d error: Can't create surface\n");
        return;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(game->screen->pRenderer, text_surface);
    if (!text_texture){
        fprintf(stderr, "consol_d error: Can't create texure\n");
        return;
    }
    drawImage(text_texture, 100, 100, game->screen->pRenderer);

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
