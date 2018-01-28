#include "texture.hpp"
#include <SDL_image.h>
#include "glad/glad.h"
#include <sys/random.h>

Texture::Texture(const char *filename, GLenum target) {
    SDL_Surface *s = IMG_Load(filename);
    this->init(s, target, true);
    SDL_FreeSurface(s);
}

Texture::Texture(SDL_Surface *surface, GLenum target) {
    this->init(surface, target, false);
}

void Texture::init(SDL_Surface * surface, GLenum target, bool flip){
    width_ = surface->w;
    height_ = surface->h;
    
    this->surf = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_PREALLOC, width_, height_, 32, surface->format->Rmask,
                    surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

    if(flip){
        SDL_LockSurface(surface);
        SDL_LockSurface(surf);
        uint8_t *dst = (uint8_t*)surf->pixels;
        uint8_t *src = (uint8_t*)surface->pixels;
        const size_t n_ints = surface->w * surface->h;
        // for(size_t idx = 0; idx < n_ints; idx++){
        //     dst[n_ints - idx -1] = src[idx];
        // }
        const int h = surf->h;
        const size_t rowbytes = surf->pitch;
        printf("Rowbytes %lu Width %lu BPP 32\n", rowbytes, surf->w);
        for(int row = 0; row < surf->h; row++){
            memcpy(&dst[rowbytes * row], &src[(h - row - 1) * rowbytes], rowbytes);
        }
        #ifdef RANDOM_TEXTURES_NO_ONE_WILL_EVER_DEFINE_THIS
        getrandom(dst, n_ints * 4, 0);
        #endif
        SDL_UnlockSurface(surface);
        SDL_UnlockSurface(surf);
    }else{
        SDL_BlitSurface(surface, NULL, surf, NULL);
    }
    pixels_ = surf->pixels;

    glGenTextures(1, &texID_);
    glBindTexture(target, texID_);

    if (surface->format->BytesPerPixel == 4) {
        format_ = GL_RGBA;
    } else {
        format_ = GL_RGB;
    }
    //
    glTexImage2D(target, 0, format_, width_, height_, 0, format_, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(target);
}

Texture::~Texture(){
    glDeleteTextures(1, &texID_);
    SDL_FreeSurface(surf);
    surf = NULL;
    pixels_ = NULL;
    width_ = -1;
    height_ = -1;
    format_ = -1;
    texID_ = -1;
}

void Texture::bind(GLenum target) {
    glBindTexture(target, texID_);
}

void Texture::unbind(GLenum target) {
    glBindTexture(target, 0);
}
