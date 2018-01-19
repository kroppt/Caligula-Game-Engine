#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "glad/glad.h"
#include <SDL2/SDL_opengl.h>
#include "audio/AudioInterface.h"
#include "shader_program.h"
#include "utils.h"
#include <vector>

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
    int res_x = 1920;
    int res_y = 1080;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *win = SDL_CreateWindow(
        "Test Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        res_x,
        res_y,
        SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    if (win == NULL) {
        printf("SDL_CreateWindow error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("Created Window\n");
    SDL_GLContext context = SDL_GL_CreateContext(win);
    if(!context){
        printf("SDL_GL_CreateContext failed %s\n", SDL_GetError());
    }
    SDL_GL_MakeCurrent(win, context);
    SDL_GL_SetSwapInterval(1);
    if (!gladLoadGL()) {
        std::cout << "gladLoadGL error" << std::endl;
        SDL_Quit();
        return 1;
    }

    const char *vertexShaderFilename = "vertex_shader.vsh";
    const char *fragmentShaderFilename = "fragment_shader.fsh";
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderFilename);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
    
    std::vector<GLuint> shaderList;
    shaderList.push_back(vertexShader);
    shaderList.push_back(fragmentShader);

    ShaderProgram shaderProgram(shaderList);
    SDL_Event event;
    bool running = true;
    loadSound("test", "audio/test.mpcm");
    while(running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    playSnd("test", 0,0,0,0,1.0);
                    break;
            }
        }
        SDL_Delay(1);
    }
    // Wait 3 seconds
    SDL_Delay(3000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Reached end of file successfully." << std::endl;
    quitAudio();
    return 0;
}