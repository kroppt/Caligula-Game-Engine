#ifndef VAO_H
#define VAO_H
#include <stddef.h>
#include "glad/glad.h"

class VAO{
    public:
        VAO(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices);
        ~VAO();
        void render(void);
    private:
        GLuint vao_, vbo_, ibo_;
        float *vertices_;
        unsigned *indices_;
        size_t nVertices_, nIndices_;

};

#endif