#ifndef WINDOW_H
#define WINDOW_H 1

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
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


class Window{
    public:
        Window(const char *name, int width, int height);
        float getAspectRatio() { return (float) width_ / (float) height_; }
        SDL_Window* getWindow() { return window_; }
        void destroy(void);
        void swapBuffer(void);
        void delay(int);
    private:
        SDL_Window *window_;
        SDL_GLContext context_;
        int width_, height_;

};


#endif