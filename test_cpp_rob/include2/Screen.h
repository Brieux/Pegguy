#ifndef SCREEN_H
#define SCREEN_H

#include "defs.h"

class Screen{
    private:
        SDL_Window *p_Window;
        SDL_Renderer *p_Renderer;
    public:
        Screen(const char *title = "");
        ~Screen();
        SDL_Window *Get_Window();
        SDL_Renderer *Get_Renderer();
};

#endif