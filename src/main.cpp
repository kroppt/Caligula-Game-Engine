#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "nus/linalg.h"
#include "glad/glad.h"
#include <SDL2/SDL_opengl.h>
#include "audio/AudioInterface.h"
#include "shader_program.h"
#include "textrender.h"
#include "nus/io.h"
#include <vector>
#include "vao.h"
#include <SDL_image.h>
#include "texture.h"
#include "entity.h"

void init(void);
void setup(void);

int main(int argc, char** argv){
    init();

    int res_x = 1920;
    int res_y = 1080;
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

    setup();
    TextRender text_render = TextRender();
    text_render.ChangeFontSize(FONTSIZE_LARGE);
    text_render.ChangeFontRGBA(1., 0., 1., 1);
    text_render.ChangeFontBackgroundRGBA(0., 1., 1., 1);
    text_render.WriteText("This is a... test!");

    const char *vertexShaderFilename = "vertex_shader.vsh";
    const char *fragmentShaderFilename = "fragment_shader.fsh";
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderFilename);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
    
    std::vector<GLuint> shaderList;
    shaderList.push_back(vertexShader);
    shaderList.push_back(fragmentShader);

    ShaderProgram shaderProgram(shaderList);
    shaderProgram.bind();
    mat4 worldToCamera; mat4_set_identity(&worldToCamera);
    Entity *torus = new Entity("resources/dragon.ply", "out.png");
    GLint modelToWorldLocation  = glGetUniformLocation(shaderProgram.getProgramID(), "modelToWorld" );
    GLint worldToCameraLocation = glGetUniformLocation(shaderProgram.getProgramID(), "worldToCamera");
    glUniformMatrix4fv(worldToCameraLocation, 1, false, (float*)&worldToCamera.m);
    SDL_Event event;
    bool running = true;
    loadSound("test", "audio/sh.mpcm");
    while(running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE: running = false; break;
                        case SDLK_LEFT: torus->rotation_.y += 0.01f; break;
                        case SDLK_RIGHT: torus->rotation_.y -= 0.01f; break;
                        case SDLK_UP: torus->rotation_.z += 0.01f; break;
                        case SDLK_DOWN: torus->rotation_.z -= 0.01f; break;
                        default: playSnd("test", 1,1,1,1,1); break;
                    }
                    break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        torus->render(0, modelToWorldLocation);
        SDL_GL_SwapWindow(win);
        SDL_Delay(1);
    }

    shaderProgram.unbind();

    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Reached end of file successfully." << std::endl;
    quitAudio();
    return 0;
}

void init(){
    printf("Initializing Caligula version 0\n");
    initAudio();
    printf("Initialized Audio\n");
    // Initialize video only to avoid failure
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    printf("Initialized SDL\n");

    IMG_Init(IMG_INIT_JPG);
    IMG_Init(IMG_INIT_PNG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void setup(){
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);
    // face culling
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    // depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glDepthFunc(GL_LESS);
    glDepthRange(0.01f, 1.0f);
    glEnable(GL_DEPTH_CLAMP);
    // alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

}