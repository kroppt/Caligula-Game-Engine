#include "window.hpp"
#include <stdexcept>
#include <sstream>

Window::Window(const char *name, int width, int height){
    width_ = width;
    height_ = height;
    window_ = SDL_CreateWindow(
        name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    if (window_ == NULL) {
        printf("SDL_CreateWindow error %s\n", SDL_GetError());
        std::ostringstream oss;
        oss << "SDL_CreateWindow error " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::invalid_argument(oss.str());

    }
    context_ = SDL_GL_CreateContext(window_);
    if(!context_){
        printf("SDL_GL_CreateContext failed %s\n", SDL_GetError());
        std::ostringstream oss;
        oss << "SDL_GL_CreateContext failed " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::invalid_argument(oss.str());
    }
    SDL_GL_MakeCurrent(window_, context_);
    SDL_GL_SetSwapInterval(1);
}

void Window::destroy(){
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::swapBuffer(){
    SDL_GL_SwapWindow(window_);
}

void Window::delay(int ms){
    SDL_Delay(ms);
}