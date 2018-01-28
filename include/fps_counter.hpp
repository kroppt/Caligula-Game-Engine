#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP 1

#include <stdint.h>
#include "texture.hpp"
#include "resource_manager.hpp"
#include "textrender.hpp"
#include "entity.hpp"
#include <time.h>

class FPSCounter{
public:
    FPSCounter(TextRender *render);
    ~FPSCounter();
    void frame();
    void drawFps(uint modelOrthoLocation);
private:
    uint fps_counter, fps, now;
    Texture *fps_texture;
    TextRender *render;
    Model *square;
    Entity *fps_square;
};

#endif