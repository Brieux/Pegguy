#ifndef IA_H
#define IA_H

#include "defs.h"

typedef struct{
    int x, Vx;
    int y, Vy;
    int h, w;
}Coord_t;

typedef struct mob_w{

}mob_w;

typedef enum {B1=74/*J*/, BEBE}mob_type;

typedef struct mob{
    void (*p_mob_fun) (struct mob*, Game*);                    //Pointeur sur la fonction du mob
    mob_type type;
    Coord_t *coord;
    int life;
    bool can_jump;
    int h_jump, act_jump;
    mob_w *weapon;
    int contact;
    bool solid;
    bool gravite;
    int nb_frame;
    SDL_Texture **image;
    struct mob *mob_next;
}mob;

void mob_test(int, void*);
mob *init_monster(Game*, mob*, mob_type, int, int);
void add_monster(Game *game, mob_type type, int x, int y);
void mob_gravite(Game *game, mob *mob);
void mob_gestion(Game *game);
void draw_mob(Game *game, mob *mob);
bool collisionProjectil(Game *game, mob *mob, int type);
bool collision_perso(Game* game, mob *mob);
bool collision_mob(Game* game, mob *monstre, int diff_x);
void hurt_perso(Game *game, int deg);
void B1_fun(mob*, Game*);
void BEBE_fun(mob*, Game*);

#endif
