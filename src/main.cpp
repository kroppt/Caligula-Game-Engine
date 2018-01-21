#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
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
#include "model.h"

void gl_setup(void);

int main(int argc, char** argv){
    printf("Initializing Caligula version 0\n");
    // initAudio();
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

    IMG_Init(IMG_INIT_JPG);
    IMG_Init(IMG_INIT_PNG);

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

    gl_setup();
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

    // green square
    float vertices[] =
    {
        /*x, y, z, r, g, b, a, s, t*/
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };

    float tcoords[] =
    {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    unsigned indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    const unsigned nVertices = 4, nIndices = 6, nTcoords = 4;

    Texture texture("out.png");
    texture.bind();

    //VAO vao(vertices, indices, tcoords, nVertices, nIndices, nTcoords);
    VAO *vao = loadVAOfromOBJ("resources/torus.obj");

    SDL_Event event;
    bool running = true;
    // loadSound("test", "audio/sh.mpcm");
    while(running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                    // playSnd("test", 1,1,1,1,1);
                    break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vao->render();
        SDL_GL_SwapWindow(win);
        SDL_Delay(1);
    }

    texture.unbind();
    shaderProgram.unbind();

    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Reached end of file successfully." << std::endl;
    // quitAudio();
    return 0;
}

void gl_setup(){
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    // glEnable(GL_MULTISAMPLE);
    // // face culling
    // // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);
    // // depth test
    // glEnable(GL_DEPTH_TEST);
    // glDepthMask(true);
    // glDepthFunc(GL_LESS);
    // glDepthRange(0.01f, 1.0f);
    // glEnable(GL_DEPTH_CLAMP);
    // // alpha blending
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);

}