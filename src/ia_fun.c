#include "../include/ia.h"//Penser à mettre ça dans defs.h

void mob_test(int line, void *p){
    if (!p){
        fprintf(stderr, "Error line %d, pointer NULL\n", line);
        exit(EXIT_FAILURE);
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
            creature->coord->h = 32;
            creature->coord->w = 32;
            creature->can_jump = false;
            creature->h_jump = creature->v_jump = 0;
            creature->weapon = NULL;
            creature->solid = true;
            creature->gravite = true;
            creature->image = NULL; //A dessiner
            creature->mob_next = NULL;

            //POINTEUR B1_FUN !
        break;

        default:
            fprintf(stderr, "Error in init_monster, wrong mob_type\n");
            exit(EXIT_FAILURE);
          break;
    }
    if (previous){
        previous->mob_next = creature;
        return creature;
    } else {
        return creature;
    }


}


void B1_fun(mob* mob, Game* game){
    
}