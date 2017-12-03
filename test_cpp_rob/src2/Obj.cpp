#include "defs.h"

using namespace std;

static SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer){
    SDL_Surface *surface = IMG_Load(image);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_FreeSurface(surface);

  return texture;
}

Obj::Obj(int x, int y, int h, int w, int nb_Frames, int deep_Image,
    const char* img, type_t type, bool solid, bool active):
    x(x), y(y), h(h), w(w), nb_Frames(nb_Frames), deep_Image(deep_Image),
    type(type), solid(solid), active(active){

        cout << "création d'une instance d'un Obj\n";
        image = new SDL_Texture*[nb_frame];
        if (!image){
            cerr << "Error in Obj, can't alloc memory\n";
            exi(EXIT_FAILURE);
        }
        for (int i = 0; i < nb_frames; i++){
            image[i] = new SDL_Texture*;
            if (!image[i]){
                cerr << "Error in Obj, can't alloc memory\n"
                exi(EXIT_FAILURE);
            }

        }

    }
}

Obj::~Obj(){
    cout << "Destruction d'une instance d'un Obj\n";
    for (int i = 0; i < nb_frames; i++){
        delete image[i];
    }
    delete image;
}
