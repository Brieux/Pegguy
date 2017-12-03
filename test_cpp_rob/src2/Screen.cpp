#include "defs.h"

using namespace std;

Screen::Screen(const char *title){
    cout << "Création d'une instance de Screen\n";
    if (SDL_Init(SDL_INIT_VIDEO)){
        cerr << "Error, can't initialize SDL " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    p_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_W,
                                        WINDOW_H,
                                        SDL_WINDOW_SHOWN);
    if (!p_Window){
        cerr << "Error, can't initialize p_Window";
        exit(EXIT_FAILURE);
    }

    p_Renderer = SDL_CreateRenderer(p_Window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!p_Renderer){
        cerr << "Error, can't initialize p_Renderer";
        exit(EXIT_FAILURE);
    }

    if (!IMG_Init(IMG_INIT_JPG)){
        cerr << "Error, can't initialize SDL_Image : " << IMG_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    SDL_ShowCursor(SDL_DISABLE);
}

Screen::~Screen(){
    cout << "Destruction d'une instance de Screen\n";
    SDL_DestroyWindow(p_Window);
    SDL_DestroyRenderer(p_Renderer);
    IMG_Quit();
    SDL_Quit();
}
