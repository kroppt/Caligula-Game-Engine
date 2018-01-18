#include <stdio.h>
#include <SDL.h>
#include "audio/AudioInterface.h"

int main(int argc, char** argv){
    initAudio();
    SDL_Init(SDL_INIT_EVERYTHING);
    printf("Hello World\n");
    return 0;
}