#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include <SDL_image.h>

class Texture{
    public:
        Texture(const char *filename, GLenum target = GL_TEXTURE_2D);
        Texture(SDL_Surface *surface, GLenum target = GL_TEXTURE_2D);
        GLuint getTexID() { return texID_; }
        int getWidth() { return width_; }
        int getHeight() { return height_; }
        GLenum getFormat() { return format_; }
        void bind(GLenum target = GL_TEXTURE_2D);
        void unbind(GLenum target = GL_TEXTURE_2D);
        ~Texture(void);

    private:
        void init(SDL_Surface * surface, GLenum target, bool flip);
        GLuint texID_;
        int width_, height_;
        GLenum format_;
        void *pixels_;
        SDL_Surface *surf;

};

#endif
