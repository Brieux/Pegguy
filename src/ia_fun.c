#include "../include/ia.h"//Penser à mettre ça dans defs.h

void mob_test(int line, void *p){
    if (!p){
        fprintf(stderr, "Error line %d, pointer NULL\n", line);
        exit(EXIT_FAILURE);
    }
}
void mob_gravite(Game *game, mob *mob){
    if (!mob->gravite){
        return;
    }
    DynObj *dynObj = NULL;
    mob->coord->Vy += GRAVITE;

    if (mob->coord->Vy > VDOWN){
        mob->coord->Vy = VDOWN;
    }

    for (uint i=0; i<abs(mob->coord->Vy); i++){
        if (collisionMap(game, mob->coord->x, mob->coord->y + abs(mob->coord->Vy)/mob->coord->Vy,
          mob->coord->w, mob->coord->h) || //si collision avec element du decor
          collisionMapObj(game, mob->coord->x, mob->coord->y + abs(mob->coord->Vy)/mob->coord->Vy,
          mob->coord->w, mob->coord->h, 0))//si collision avec objet dynamique
        {
            //Empecher le saut de continuer
            mob->coord->Vy = 0;
            if (mob->can_jump){
                mob->act_jump = mob->h_jump;
            }
            

            if (collisionMap(game, mob->coord->x, mob->coord->y + 1,
                mob->coord->w, mob->coord->h) ||
                (dynObj = collisionMapObj(game, mob->coord->x, mob->coord->y + 1,
                mob->coord->w, mob->coord->h, 0)))//si c'etait le sol
            {
                //Reautoriser le saut
                if (mob->can_jump){
                    mob->h_jump = 0;
                }
                if (dynObj){
                    destroyBox(game, dynObj);
                }
            }
        } else {
            mob->coord->y += abs(mob->coord->Vy)/mob->coord->Vy;//sinon on modifie la position du perso
        }
    }
}

mob *init_monster(Game *game, mob *previous,mob_type type, int x, int y){
    mob *creature = malloc(sizeof(mob));
    mob_test(__LINE__, creature);
    creature->coord = malloc(sizeof(Coord_t));
    mob_test(__LINE__, creature->coord);
    *(creature->coord) = (Coord_t) {x=x, y=y};
    creature->type = type;
    switch (type){
        case B1:
            creature->life = 3;
            creature->coord->h = 32;
            creature->coord->w = 32;
            creature->coord->Vx = 2;
            creature->can_jump = false;
            creature->h_jump = creature->act_jump = 0;
            creature->weapon = NULL;
            creature->solid = true;
            creature->gravite = true;
            creature->nb_frame = 2;
            creature->image = malloc(creature->nb_frame * sizeof(SDL_Texture *)); //A dessiner
            creature->mob_next = NULL;
            creature->p_mob_fun = B1_fun;
        break;

        default:
            fprintf(stderr, "Error in init_monster, wrong mob_type\n");
            exit(EXIT_FAILURE);
          break;
    }
    if (previous){
        previous->mob_next = creature;
        return game->first_mob; 
    } else {
        return creature;
    }


}

void draw_mob(Game *game, mob *mob){
    int dep_x;  
    int dep_y;

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
    } else {
        dep_y = 0;
    }
    int x_act = mob->coord->x - dep_x;
    int y_act = mob->coord->y - dep_y;
    if (x_act > dep_x && x_act < WINDOW_W + dep_x){ //Formule a tester
        if (y_act > dep_y && y_act < WINDOW_H + dep_y){
            drawImage(mob->image[0], x_act, y_act, game->screen->pRenderer);
        }
    }
    
}

void mob_gestion(Game *game){
    mob *p_mob = game->first_mob;
    while (p_mob){
        mob_gravite(game, p_mob);
        draw_mob(game, p_mob);
        p_mob->p_mob_fun(p_mob, game);
        p_mob = p_mob->mob_next;
    }
}

void B1_fun(mob* mob, Game* game){
    int x_enemy = game->perso->x;
    if (x_enemy > mob->coord->x){
        if (!collisionMap(game, mob->coord->x + 1, mob->coord->y, mob->coord->w, mob->coord->h)){
            mob->coord->x += mob->coord->Vx;
        }
    } else {
        if (!collisionMap(game, mob->coord->x - 1, mob->coord->y, mob->coord->w, mob->coord->h)){
            mob->coord->x -= mob->coord->Vx;
        }
    }
}