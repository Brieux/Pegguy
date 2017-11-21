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

typedef enum {B1}mob_type;

typedef struct mob{
    void (*p_mob_fun) (struct mob*, Game*);                    //Pointeur sur la fonction du mob
    mob_type type;
    Coord_t *coord;
    bool can_jump;
    int h_jump, act_jump;
    mob_w *weapon;
    int contact;
    bool solid;
    bool gravite;
    SDL_Texture *image;
    struct mob *mob_next;
}mob;

void mob_test(int, void*);
mob *init_monster(Game*, mob*, mob_type, int, int);
void mob_gravite(Game *game, mob *mob);
void B1_fun(mob*, Game*);

#endif