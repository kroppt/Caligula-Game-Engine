#ifndef ENTITY_H
#define ENTITY_H
#include "vao.h"
#include "texture.h"

VAO* loadVAOfromOBJ(const char *modelFilename);

class Entity{
    public:
        Entity(VAO *vao, Texture *texture);
        Entity(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, Texture *texture);
        Entity(VAO *vao, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
        Entity(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
        Entity(const char *modelFilename, Texture *texture);
        Entity(const char *modelFilename, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
    private:
        VAO *vao_;
        Texture *texture_;

};

#endif