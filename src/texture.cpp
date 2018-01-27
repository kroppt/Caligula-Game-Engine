#include "texture.hpp"
#include <SDL_image.h>
#include "glad/glad.h"

Texture::Texture(const char *filename, GLenum target) : Texture(IMG_Load(filename)) {}

Texture::Texture(SDL_Surface *surface, GLenum target) {
    width_ = surface->w;
    height_ = surface->h;
    pixels_ = surface->pixels;

    glGenTextures(1, &texID_);
    glBindTexture(target, texID_);

    if (surface->format->BytesPerPixel == 4) {
        format_ = GL_RGBA;
    } else {
        format_ = GL_RGB;
    }

    glTexImage2D(target, 0, format_, width_, height_, 0, format_, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(target);
}

void Texture::bind(GLenum target) {
    glBindTexture(target, texID_);
}

void Texture::unbind(GLenum target) {
    glBindTexture(target, 0);
}
