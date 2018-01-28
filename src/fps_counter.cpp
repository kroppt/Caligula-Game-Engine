#include "fps_counter.hpp"
#define COUNT_OF(x) (sizeof(x)/sizeof(x[0]))
FPSCounter::FPSCounter(TextRender *render){
    fps_counter = 0;
    fps = 0;
    fps_texture = render->WriteText("FPS: PLACEHOLDER");
    now = time(NULL);
    this->render = render;

    float modelC[] = {
        //12-D vertices (x,y,z,r,g,b,a,s,t,nx,ny,nz)
        0,0,0 , 1,1,1,1 , 0,0 , 0, 0, 0,
        0,72,0 , 1,1,1,1 , 0,1 , 0, 0, 0,
        338,72,0 , 1,1,1,1 , 1,1 , 0, 0, 0,
        338,0,0 , 1,1,1,1 , 1,0 , 0, 0, 0,
    };

    uint indices[] = { 0, 1, 2, 2, 3, 0};

    square = new Model(&modelC[0], &indices[0], COUNT_OF(modelC), COUNT_OF(indices));
    fps_square = new Entity(square, fps_texture);
    fps_square->position = glm::vec3(0,0,0);
    fps_square->scale = 1.0f;
    fps_square->disableLighting = true;
}
FPSCounter::~FPSCounter(){
    delete fps_square;
    delete fps_texture;
    delete square;
}
void FPSCounter::frame(){
    this->fps_counter++;
    if(time(NULL) - now > 0){
        fps = fps_counter;
        fps_counter = 0;
        delete fps_texture;
        //printf("FPS %d\n", fps);
        fps_texture = render->WriteText((std::string("FPS: ") + std::to_string(fps)).c_str());
        fps_square->texture_ = fps_texture;
        now = time(NULL);
    }
}
void FPSCounter::drawFps(uint modelOrthoLocation){
    fps_square->render(0, modelOrthoLocation);
}