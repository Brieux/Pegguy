#include "../include/ia.h"

void mob_test(int line, void *p){
    if (!p){
        fprintf(stderr, "Error line %d, pointer NULL\n", line);
        exit(EXIT_FAILURE);
    }
}

void add_monster(Game *game, mob_type type, int x, int y){
    mob *mob = game->first_mob;
    while(mob && mob->mob_next){
        mob = mob->mob_next;
    }
    game->first_mob = init_monster(game, mob, type, x, y);
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
    creature->type = type;
    creature->coord->x = x;
    creature->coord->y = y;
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
            creature->nb_frame = 1;
            creature->image = malloc(creature->nb_frame * sizeof(SDL_Texture *)); //A dessiner
            creature->image[0] = loadTexture("../graphics/ghost.png", game->screen->pRenderer);
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

    calcul_dep(&dep_x, &dep_y, game);

   if (mob->coord->x > dep_x && mob->coord->x + mob->coord->w < WINDOW_W + dep_x){ //Formule a tester
        if (mob->coord->y + mob->coord->h > dep_y && mob->coord->y < WINDOW_H + dep_y){
            drawImage(mob->image[0], mob->coord->x - dep_x, mob->coord->y - dep_y, game->screen->pRenderer);
        }
    }


}

void mob_gestion(Game *game){
    mob *p_mob = game->first_mob;
    while (p_mob){
        mob_gravite(game, p_mob);

        p_mob->p_mob_fun(p_mob, game);
        p_mob = p_mob->mob_next;
    }
}
bool collisionProjectil(Game *game, mob *mob){
    Projectile *p_projectile = game->projectiles;
    while (p_projectile){   //Si toucher détruire projectile
        if (collision(p_projectile->dynObj->x, p_projectile->dynObj->y,
                        p_projectile->dynObj->w, p_projectile->dynObj->h,
                        mob->coord->x, mob->coord->y, mob->coord->w, mob->coord->h)){
            deleteProjectile(game, p_projectile);
            return true;
        }
        p_projectile = p_projectile->following;
    }
    return false;
}

void destroy_mob(Game *game, mob *c_mob){
    mob_test(__LINE__, c_mob);

    mob *p_mob = game->first_mob;
    while (p_mob->mob_next && p_mob->mob_next != c_mob){
        p_mob = p_mob->mob_next;
    }
    if (c_mob == game->first_mob && !game->first_mob->mob_next){
        free(c_mob->coord);
        free(c_mob);
        game->first_mob = NULL;
    } else if (c_mob == game->first_mob && game->first_mob->mob_next){
        game->first_mob = game->first_mob->mob_next;
    } else {
        if (c_mob->mob_next){
            p_mob->mob_next = c_mob->mob_next;
        } else {
            p_mob->mob_next = NULL;
        }
        free(c_mob->coord);
        free(c_mob);
    }
}

bool collision_perso(Game* game, mob *mob){
    return collision(game->perso->x, game->perso->y, game->perso->w,
                    game->perso->h, mob->coord->x, mob->coord->y,
                    mob->coord->w, mob->coord->h
    );
}

bool collision_mob(Game* game, mob *monstre, int diff_x){
    mob *p_mob = game->first_mob;
    while (p_mob){
        if (p_mob == monstre){
            if (monstre->mob_next){
                p_mob = monstre->mob_next;
                continue;
            } else {
                return false;
            }
        }
        if (
            collision(p_mob->coord->x, p_mob->coord->y,
                    p_mob->coord->w, p_mob->coord->h, 
                    monstre->coord->x + diff_x, monstre->coord->y,
                    monstre->coord->w, monstre->coord->h
            )){
                return true;
            }
        p_mob = p_mob->mob_next;
    }
    return false;
}
/*
**************************************************
*   Fonctions des mobs !                         *
**************************************************
*/
void B1_fun(mob* mob, Game* game){
    if (collisionProjectil(game, mob)){
        mob->life--;
    }
    if (mob->life <= 0){
        destroy_mob(game, mob);
    }
    if (collision_perso(game, mob)){
        if (!game->perso->invincible){
            game->perso->hp--;
            game->perso->invincible = 100;
        }
    }
    int x_enemy = game->perso->x;
    if (x_enemy > mob->coord->x){
        if (!collisionMap(game, mob->coord->x + mob->coord->Vx, mob->coord->y, mob->coord->w, mob->coord->h)){
            if (!collisionMapObj(game, mob->coord->x + mob->coord->Vx, mob->coord->y, mob->coord->w, mob->coord->h, NULL)){
                if (!collision_mob(game, mob, mob->coord->Vx)){
                    mob->coord->x += mob->coord->Vx;
                }
            }
        }
    } else {
        if (!collisionMap(game, mob->coord->x - 1, mob->coord->y, mob->coord->w, mob->coord->h)){
            if (!collisionMapObj(game, mob->coord->x - 1, mob->coord->y, mob->coord->w, mob->coord->h, NULL)){
                if (!collision_mob(game, mob, -mob->coord->Vx)){
                    mob->coord->x -= mob->coord->Vx;
                }
            }
        }
    }
}
