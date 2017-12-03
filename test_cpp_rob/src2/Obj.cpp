#include "defs.h"

using namespace std;

static SDL_Texture *loadTexture(char *image, SDL_Renderer *pRenderer){
    SDL_Surface *surface = IMG_Load(image);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_FreeSurface(surface);

  return texture;
}

static void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *pRenderer){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(pRenderer, texture, NULL, &dest);
}

Obj::Obj(int x, int y, int h, int w, int nb_Frames, int deep_Image,\
    const char* img, int type, bool solid, bool active):
    x(x), y(y), h(h), w(w), nb_Frames(nb_Frames), deep_Image(deep_Image),
    type(type), solid(solid), active(active){

        char sprite_name[128];
        strcpy(sprite_name, img);
        int end_name = 0;
        while(sprite_name[++end_name] != '\0');
        sprite_name[end_name + 1] = '\0';

        cout << "création d'une instance d'un Obj\n";
        image = new SDL_Texture*[nb_Frames];
        if (!image){
            cerr << "Error in Obj, can't alloc memory\n";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nb_Frames; i++){
            image[i] = new (SDL_Texture *);
            if (!image[i]){
                cerr << "Error in Obj, can't alloc memory\n";
                exit(EXIT_FAILURE);
            }

        }

}


Obj::~Obj(){
    cout << "Destruction d'une instance d'un Obj\n";
    for (int i = 0; i < nb_Frames; i++){
        delete image[i];
    }
    delete image;
}

int Obj::Get_x(){
    return x;
}
int Obj::Get_y(){
    return y;
}
int Obj::Get_h(){
    return h;
}
int Obj::Get_w(){
    return w;
}

void Obj::draw(Game *game){
    int dep_x;
    int dep_y;
    game->Calcul_Dep(dep_x, dep_y);
    drawImage(game->map[x + dep_x/32][y + dep_y/32]->image,
                x*32 - dep_x%32,
                y*32 - dep_y%32,
                game->screen->pRenderer
    );

}
