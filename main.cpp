#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <GL/glx.h>
#include <SDL2/SDL_opengl.h>
#include "audio/AudioInterface.h"

int main(int argc, char** argv){
    printf("Initializing Caligula version 0\n");
    initAudio();
    printf("Initialized Audio\n");
    // Initialize video only to avoid failure
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("Initialized SDL\n");
    int res_x = 1280;
    int res_y = 720;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

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
    printf("Created Window\n");
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);
    SDL_GL_SetSwapInterval(1);
    if (!gladLoadGL()) {
        GLXContext glx = glXGetCurrentContext();
        if(!glx){
            printf("NO GLX CONTEXT!\n");
        }
        std::cout << "gladLoadGL error" << std::endl;
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