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

Obj::Obj(int x, int y, int h, int w, int nb_Frames, float time_Frame, int deep_Image,\
    const char* img, int type, bool solid, bool active, Game *game):
    x(x), y(y), h(h), w(w), nb_Frames(nb_Frames), deep_Image(deep_Image),
    type(type), solid(solid), active(active), time_Frame(time_Frame){

        char sprite_name[128];
        strcpy(sprite_name, img);
        int end_name = 0;
        while(sprite_name[++end_name] != '\0');
        sprite_name[end_name + 1] = '\0';

        //S'occuper du chargement des sprites !
        cout << "création d'une instance d'un Obj\n";
        image = (SDL_Texture**) malloc(nb_Frames * sizeof(struct SDL_Texture**));
        if (!image){
            cerr << "Error in Obj, can't alloc memory\n";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nb_Frames; i++){
            image[i] = (SDL_Texture*) malloc(sizeof(struct SDL_Texture*));
            if (!image[i]){
                cerr << "Error in Obj, can't alloc memory\n";
                exit(EXIT_FAILURE);
            }
            image[i] = loadTexture(sprite_name, game->Get_Screen()->Get_Renderer());

        }

}


Obj::~Obj(){
    cout << "Destruction d'une instance d'un Obj\n";
    for (int i = 0; i < nb_Frames; i++){
        free(image[i]);
    }
    free(image);
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
    Uint32 time_Sdl = SDL_GetTicks();
    int index_frame = (int)((time_Sdl/1000)/time_Frame)%nb_Frames;   //A vérifier
    int dep_x;
    int dep_y;
    game->Calcul_Dep(dep_x, dep_y);
    drawImage(image[index_frame],
                x - dep_x,
                y - dep_y,
                game->Get_Screen()->Get_Renderer()
    );

}
