#define SDL_MAIN_HANDLED  

#include "../include/Application.h"
#include <SDL2/SDL.h>
#include <iostream>

int main() {
    SDL_SetMainReady();  // initialize

    Application app;
    if (!app.Initialize()) {
        std::cerr << "Application failed to initialize." << std::endl;
        return -1;
    }

    app.Run(60);

    return 0;
}
