#ifndef VAO_H
#define VAO_H
#include <stddef.h>
#include "glad/glad.h"

class VAO{
    public:
        VAO(float *vertices, unsigned *indices, float *tcoords, size_t nVertices, size_t nIndices, size_t nTcoords);
        ~VAO();
        void render(void);
    private:
        GLuint vao_, vbo_, ibo_, txbo_;
        float *vertices_, *tcoords_;
        unsigned *indices_;
        size_t nVertices_, nIndices_, nTcoords_;

};

#endif