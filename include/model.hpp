#ifndef MODEL_H
#define MODEL_H
#include <stddef.h>
#include "glad/glad.h"

class Model{
    public:
        Model(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices);
        ~Model();
        void render(void);
    private:
        GLuint vao_, vbo_, ibo_;
        float *vertices_;
        unsigned *indices_;
        size_t nVertices_, nIndices_;

};

Model* loadModelfromPLY(const char *modelFilename);

#endif