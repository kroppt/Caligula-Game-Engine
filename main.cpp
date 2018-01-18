#include <iostream>
#include <SDL.h>
#include "audio/AudioInterface.h"

int main(int argc, char** argv){
    initAudio();
    // Initialize video only to avoid failure
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    int res_x = 1280;
    int res_y = 720;
    SDL_Window *win = SDL_CreateWindow(
        "Test Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        res_x,
        res_y,
        SDL_WINDOW_SHOWN);
    if (win == NULL) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // Wait 3 seconds
    SDL_Delay(3000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Reached end of file successfully." << std::endl;
    return 0;
}