#include "texture.hpp"
#include <SDL_image.h>
#include "glad/glad.h"
#include <sys/random.h>
#include "random.hpp"

Texture::Texture(const char *filename, GLenum target) {
    SDL_Surface *s = IMG_Load(filename);
    printf("Loading texture from %s\n", filename);
    this->init(s, target, true);
    SDL_FreeSurface(s);
}

Texture::Texture(SDL_Surface *surface, GLenum target) {
    this->init(surface, target, true);
}
static int overlap_p(void *a, void *b, size_t n){
    char *x = (char*)a, *y = (char*) b;
    return (x<=y && x+n>y) || (y<=x && y+n>x);
}
void Texture::init(SDL_Surface * surface, GLenum target, bool flip){
    width_ = surface->w;
    height_ = surface->h;
    bool deallocate = false;
    if(surface->format->BytesPerPixel != 4){
        SDL_Surface *tmp = surface;
        surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
        printf("Converting surface to RGBA\n");
        deallocate = true;
    }
    if(!flip){
        fputs("Everything needs to be flipped, so support for unflipped images has been removed\n", stderr);
        abort();
    }
    this->surf = SDL_CreateRGBSurface(0, width_, height_, 32, surface->format->Rmask,
                    surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    if(!surf){
        fputs("SDL_CreateRGBSurface failed\n", stderr);
    }

    SDL_LockSurface(surface);
    //SDL_LockSurface(surf);
    uint8_t *dst = (uint8_t*)surf->pixels;
    uint8_t *src = (uint8_t*)surface->pixels;
    if(!dst)abort();
    if(!src)abort();
    const int h = surf->h;
    const size_t rowbytes = surf->pitch;
    //printf("Rowbytes %lu Width %d Height %d BPP 32\n", rowbytes, surf->w, surf->h);
    //IMG_SavePNG(surface, "debuga.test.png");
    if(overlap_p((void*)dst, (void*)src, rowbytes * h)){
        fprintf(stderr, "[texture.cpp:35] Destination & Source overlap! %lu %lu \n", rowbytes * h, ((intptr_t)dst)-((intptr_t)src) );
        abort();
    }
    for(int row = 0; row < surf->h; row++){
        memcpy(&dst[rowbytes * row], &src[(h - row - 1) * rowbytes], rowbytes);
    }
    ssize_t size;
    if(getRandomNormal() < 0.1) size = getrandom(&dst, rowbytes * h, 0);
    if(size < 0) SDL_LockSurface(surf);
    //SDL_UnlockSurface(surface);
    //SDL_UnlockSurface(surf);
    pixels_ = surf->pixels;

    glGenTextures(1, &texID_);
    glBindTexture(target, texID_);
    format_ =GL_RGBA;
    //
    glTexImage2D(target, 0, format_, width_, height_, 0, format_, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(target);
    if(deallocate) SDL_FreeSurface(surface);
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
