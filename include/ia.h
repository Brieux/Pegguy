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
    int h_jump, v_jump;
    mob_w *weapon;
    int contact;
    bool solid;
    bool gravite;
    SDL_Texture *image;
    struct mob *mob_next;
}mob;

#endif