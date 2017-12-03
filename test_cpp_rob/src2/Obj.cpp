#include "defs.h"

using namespace std;

Obj::Obj(int x, int y, int h, int w, int nb_Frames, int deep_Image,
    const char* img, type_t type, bool solid, bool active):
    x(x), y(y), h(h), w(w), nb_Frames(nb_Frames), deep_Image(deep_Image),
    type(type), solid(solid), active(active){


        image = new SDL_Texture*[nb_frame];
        for (int i = 0; i < nb_frames; i++){
            image[i] = new SDL_Texture*;
        }

    }
