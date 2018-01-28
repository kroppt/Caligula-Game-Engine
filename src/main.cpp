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

#define COUNT_OF(x) (sizeof(x)/sizeof(x[0]))

void init(void);
void setup(void);

int main(int argc, char** argv){
    init();

    int res_x = 1800;
    int res_y = 900;
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
    SDL_GL_SetSwapInterval(0);
    if (!gladLoadGL()) {
        std::cout << "gladLoadGL error" << std::endl;
        SDL_Quit();
        return 1;
    }

    setup();
    
    TextRender text_render = TextRender();
    text_render.ChangeFontSize(FONTSIZE_LARGE);
    text_render.ChangeFontRGBA(1., 0., 1., 1);
    text_render.ChangeFontBackgroundRGBA(0., 0., .3, 1);
    Texture *textTexture = text_render.WriteText("This is a... texture test!");

    ShaderProgram shaderProgram("vertex_shader.zap", "fragment_shader.boom");
    ShaderProgram orthoShader("resources/ortho.vsh", "resources/ortho.fsh");

    Camera *camera = new Camera(glm::vec3(0.0f,0.0f,20.0f), glm::vec3(0.0f,0.0f,0.0f));


    Entity *dragon = new Entity("resources/dragonFromObj.ply", "out.png");
    dragon->position = glm::vec3(0.0f, -4.2f, -6.8f);
    Entity *lightbox = new Entity("resources/cube.ply", "resources/white_square.png");
    lightbox->position = glm::vec3(3,3,3);
    lightbox->scale = 0.05f;

    Model *cubeModel = loadModelfromPLY("resources/cubeTexture.ply");
    float modelC[] = {
        //12-D vertices (x,y,z,r,g,b,a,s,t,nx,ny,nz)
        0,0,0 , 1,1,1,1 , 0,0 , 0, 0, 0,
        0,72,0 , 1,1,1,1 , 0,1 , 0, 0, 0,
        338,72,0 , 1,1,1,1 , 1,1 , 0, 0, 0,
        338,0,0 , 1,1,1,1 , 1,0 , 0, 0, 0,
    };

    uint indices[] = { 0, 1, 2, 2, 3, 0};

    Model *square = new Model(&modelC[0], &indices[0], COUNT_OF(modelC), COUNT_OF(indices));
    Texture *backTexture = new Texture("resources/graphWithSun.png"); //Screenshot from 2018-01-21 22-30-09.png");
    Entity *FPSCube = new Entity(square, backTexture);
    FPSCube->position = glm::vec3(0,0,0);
    FPSCube->scale = 1.0f;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)res_x / (float)res_y, 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 vp = projection * view;

    GLint modelLocation  = glGetUniformLocation(shaderProgram.getProgramID(), "model" );
    GLint modelOrthoLocation  = glGetUniformLocation(orthoShader.getProgramID(), "model" );
    GLint viewLocation  = glGetUniformLocation(shaderProgram.getProgramID(), "view" );
    GLint projectionLocation  = glGetUniformLocation(shaderProgram.getProgramID(), "projection" );
    GLint vpLocation = glGetUniformLocation(shaderProgram.getProgramID(), "vp");
    GLint ldLocation = glGetUniformLocation(shaderProgram.getProgramID(), "lightingDisable");

    GLint sizeLocation = glGetUniformLocation(orthoShader.getProgramID(), "screenSize" );
    orthoShader.bind();
    glUniform2f(sizeLocation, res_x, res_y);

    shaderProgram.bind();
    glUniformMatrix4fv(vpLocation, 1, false, &vp[0][0]);
    glUniformMatrix4fv(viewLocation, 1, false, &view[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, false, &projection[0][0]);
    glUniform1i(ldLocation, 0);

    SDL_Event event;
    bool running = true;
    loadSound("test", "audio/sh.mpcm");
    uint fps_counter = 0, fps = 0;
    uint now = time(NULL);
    Texture *fps_texture = text_render.WriteText("FPS: PLACEHOLDER");
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
                        case SDLK_w: dragon->position.y += 0.1f; break;
                        case SDLK_s: dragon->position.y -= 0.1f; break;
                        case SDLK_d: dragon->position.x += 0.1f; break;
                        case SDLK_a: dragon->position.x -= 0.1f; break;
                        case SDLK_q: dragon->position.z += 0.1f; break;
                        case SDLK_e: dragon->position.z -= 0.1f; break;
                        #ifndef NO_CAMERA_MOVE
                        case SDLK_u: camera->position.y += 0.1f; break;
                        case SDLK_o: camera->position.y -= 0.1f; break;
                        case SDLK_j: camera->position.x += 0.1f; break;
                        case SDLK_l: camera->position.x -= 0.1f; break;
                        case SDLK_i: camera->position.z += 0.1f; break;
                        case SDLK_k: camera->position.z -= 0.1f; break;
                        #endif
                        default: playSnd("test", 1,1,1,1,1); break;
                    }
                    break;
            }
        }
        #if 1
        ///////////////////////////3d rendering
        // bind the shader
        shaderProgram.bind();
        // camera update
        view = camera->getViewMatrix();
        vp = projection * view;
        glUniformMatrix4fv(vpLocation, 1, false, &vp[0][0]);
        glUniformMatrix4fv(viewLocation, 1, false, &view[0][0]);
        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniform1i(ldLocation, 0);
        dragon->render(0, modelLocation);
        glUniform1i(ldLocation, 1);
        lightbox->render(0, modelLocation);
        #endif
        ////////////////////////////////////// orthographic HUD rendering
        fps_counter++;
        if(time(NULL) - now > 0){
            fps = fps_counter;
            fps_counter = 0;
            delete fps_texture;
            printf("FPS %d\n", fps);
            fps_texture = text_render.WriteText((std::string("FPS: ") + std::to_string(fps)).c_str());
            FPSCube->texture_ = fps_texture;
            now = time(NULL);
        }
        glDisable(GL_DEPTH_TEST);
        orthoShader.bind();
        glUniform2f(sizeLocation, res_x, res_y);
        FPSCube->render(0, modelOrthoLocation);
        glEnable(GL_DEPTH_TEST);
        // update the window
        SDL_GL_SwapWindow(win);
        SDL_Delay(5);
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
