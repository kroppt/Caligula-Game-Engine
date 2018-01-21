#ifndef MODEL_H
#define MODEL_H
#include "vao.h"
#include "texture.h"

VAO* loadVAOfromOBJ(const char *modelFilename);

class Model{
    public:
        Model(VAO *vao, Texture *texture);
        Model(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, Texture *texture);
        Model(VAO *vao, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
        Model(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
        Model(const char *modelFilename, Texture *texture);
        Model(const char *modelFilename, const char *textureFilename, GLenum target = GL_TEXTURE_2D);
    private:
        VAO *vao_;
        Texture *texture_;

};

#endif