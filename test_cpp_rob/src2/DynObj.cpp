#include "defs.h"

DynObj(bool gravite, int vSpeed, int hSpeed, int count, bool linked, bool move):
            Obj(int x, int y, int h, int w, int nb_Frames, float time_Frame, int deep_Image,\
                const char* img, int type, bool solid, bool active, Game *game),\
                gravite(gravite), vSpeed(vSpeed), hSpeed(hSpeed), count(count),\
                 linked(linked), move(move){
    cout << "Création d'une instance de DynObj\n";
    //Yaura du taff avec le ciblage ici
}
~DynObj(){
    cout << "Destruction d'une instance de DynObj\n";
}
void move(){
    x += hSpeed;
    //Faire les collisions puis appliquer la gravité !
}
void manageCount(int diff);
