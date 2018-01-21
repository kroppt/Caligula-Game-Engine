#include "vao.h"
#include "glad/glad.h"
#include <stdio.h>

VAO::VAO(float *vertices, unsigned *indices, float *tcoords, size_t nVertices, size_t nIndices, size_t nTcoords) :
 vertices_(vertices), indices_(indices), tcoords_(tcoords), nVertices_(nVertices), nIndices_(nIndices), nTcoords_(nTcoords) {
    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // set up vertex buffer
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices * 7, vertices, GL_STATIC_DRAW);

    const GLsizei vertexStride = 7 * sizeof(float);

    // how to use the 7-D vertices (x,y,z,r,g,b,a), and use currently bound VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexStride, (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // set up texture coordinate buffer
    glGenBuffers(1, &txbo_);
    glBindBuffer(GL_ARRAY_BUFFER, txbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*tcoords) * nTcoords * 2, tcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // set up index buffer
    glGenBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices) * nIndices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void VAO::render(){
    // setup vertex array object
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // submit the draw call to the GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glDrawElements(GL_TRIANGLES, nIndices_, GL_UNSIGNED_INT, NULL);

    // cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

VAO::~VAO(){
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ibo_);
    glDeleteVertexArrays(1, &vao_);
}