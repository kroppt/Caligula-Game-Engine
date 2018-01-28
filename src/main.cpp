#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
//#include "nus/linalg.h"
#include "glad/glad.h"
#include <SDL2/SDL_opengl.h>
#include "audio/AudioInterface.h"
#include "shader_program.hpp"
#include "textrender.hpp"
#include "nus/io.h"
#include <vector>
#include "model.hpp"
#include <SDL_image.h>
#include "texture.hpp"
#include "entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"
#include "resource_manager.hpp"
#include "fps_counter.hpp"
#include "window.hpp"
#include "world.hpp"

#define COUNT_OF(x) (sizeof(x)/sizeof(x[0]))

void init(void);
void setup(void);

int main(int argc, char** argv){
    init();

    int res_x = 1800;
    int res_y = 900;
    Window *window = new Window("Test", res_x, res_y);

    if (!gladLoadGL()) {
        std::cout << "gladLoadGL error" << std::endl;
        SDL_Quit();
        return 1;
    }

    setup();
    
    TextRender *text_render = new  TextRender();
    text_render->ChangeFontSize(FONTSIZE_LARGE);
    text_render->ChangeFontRGBA(1., 0., 1., 1);
    text_render->ChangeFontBackgroundRGBA(0., 0., .3, 1);
    Texture *textTexture = text_render->WriteText("This is a... texture test!");

    ShaderProgram shaderProgram("vertex_shader.zap", "fragment_shader.boom");
    ShaderProgram orthoShader("resources/ortho.vsh", "resources/ortho.fsh");


    GLint modelLocation  = glGetUniformLocation(shaderProgram.getProgramID(), "model" );
    GLint modelOrthoLocation  = glGetUniformLocation(orthoShader.getProgramID(), "model" );
    GLint ldLocation = glGetUniformLocation(shaderProgram.getProgramID(), "lightingDisable");

    GLint sizeLocation = glGetUniformLocation(orthoShader.getProgramID(), "screenSize" );
    orthoShader.bind();
    glUniform2f(sizeLocation, res_x, res_y);

    Camera *camera = new Camera(glm::vec3(0.0f,0.0f,19.0f), glm::vec3(0.0f,0.0f,0.0f), (float)res_x / (float)res_y);
    camera->InitUniforms(shaderProgram.getProgramID());
    camera->theta = -M_PI/2;
    camera->phi = M_PI / 2.0f;

    ResourceManager *rm = new ResourceManager();

    Texture *backTexture = rm->loadTexture("resources/bad_texture.png");
    Texture *whiteTexture = rm->loadTexture("resources/white_square.png");
    Texture *dragonTexture = rm->loadTexture("resources/grass.png");

    Model *cubeM1 = rm->loadModel("resources/cube.ply");
    Model *cubeModel = rm->loadModel("resources/cubeTexture.ply");
    Model *dragonModel = rm->loadModel("resources/dragonFromObj.ply");

    World *world = new World();

    //make the dragon
    Entity *dragon = world->addEntity(dragonModel, dragonTexture, ldLocation);
    dragon->position = glm::vec3(0.0f, -4.2f, -6.8f);
    
    // make the lightbox
    Entity *lightbox = world->addEntity(cubeM1, whiteTexture, ldLocation);
    lightbox->position = glm::vec3(3,3,3);
    lightbox->scale = 0.05f;
    lightbox->disableLighting = true;
    
    // make the background cube
    Entity *cubeEnt = world->addEntity(cubeModel, backTexture, ldLocation);
    cubeEnt->disableLighting = true;
    cubeEnt->scale = 20.0;

    // upload the uniforms
    camera->UploadUniforms(shaderProgram.getProgramID());
    glUniform1i(ldLocation, 0);

    // create the fps counter
    FPSCounter *counter = new FPSCounter(text_render);

    // run the main loop
    SDL_Event event;
    bool running = true;
    loadSound("test", "audio/sh.mpcm");

    SDL_SetRelativeMouseMode(SDL_TRUE);
    while(running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE: running = false; break;
                        case SDLK_LEFT: dragon->yaw += 0.01f; break;
                        case SDLK_RIGHT: dragon->yaw -= 0.01f; break;
                        case SDLK_SLASH: dragon->roll += 0.01f; break;
                        case SDLK_PERIOD: dragon->roll -= 0.01f; break;
                        case SDLK_UP: dragon->pitch += 0.01f; break;
                        case SDLK_DOWN: dragon->pitch -= 0.01f; break;
			            case SDLK_p: std::cout << "dragon at (" << dragon->position.x << ", " << dragon->position.y << ", " << dragon->position.z << ")" << std::endl; break;
                        case SDLK_i: dragon->position.y += 0.1f; break;
                        case SDLK_k: dragon->position.y -= 0.1f; break;
                        case SDLK_l: dragon->position.x += 0.1f; break;
                        case SDLK_j: dragon->position.x -= 0.1f; break;
                        case SDLK_u: dragon->position.z += 0.1f; break;
                        case SDLK_o: dragon->position.z -= 0.1f; break;
                        case SDLK_n: SDL_SetRelativeMouseMode(SDL_FALSE);break;
                        case SDLK_c: SDL_SetRelativeMouseMode(SDL_TRUE );break;
                        case SDLK_y: playSnd("test", 1,1,1,1,1); break;
                        default: break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    camera->UpdateLook(event.motion.xrel, event.motion.yrel);
                    break;
            }
        }
        const uint8_t *keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W]){
            camera->Move(0.1, 0, 0);
        }
        if(keystates[SDL_SCANCODE_A]){
            camera->Move(0, -.1, 0);
        }
        if(keystates[SDL_SCANCODE_S]){
            camera->Move(-.1, 0, 0);
        }
        if(keystates[SDL_SCANCODE_D]){
            camera->Move(0, 0.1, 0);
        }
        if(keystates[SDL_SCANCODE_LSHIFT]){
            camera->Move(0, 0, -0.05);
        }
        if(keystates[SDL_SCANCODE_SPACE]){
            camera->Move(0, 0, 0.05);
        }
        ///////////////////////////3d rendering
        // bind the shader
        shaderProgram.bind();
        // camera update
        camera->update();
        camera->UploadUniforms(shaderProgram.getProgramID());
        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world->render(0, modelLocation);
        // update fps
        counter->frame();
        ////////////////////////////////////// orthographic HUD rendering
        glDisable(GL_DEPTH_TEST);
        orthoShader.bind();
        glUniform2f(sizeLocation, res_x, res_y);
        counter->drawFps(modelOrthoLocation);
        glEnable(GL_DEPTH_TEST);

        // update the window
        window->swapBuffer();
        window->delay(1);
    }

    shaderProgram.unbind();

    window->destroy();
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
    //glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);
    // face culling
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    // depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    //glClearDepth(0);
    //glDepthFunc(GL_GREATER);
    glDepthRange(0.01f, 1.0f);
    glEnable(GL_DEPTH_CLAMP);
    // alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

}
