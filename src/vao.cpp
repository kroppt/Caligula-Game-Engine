#include "random.hpp"
#include "vao.hpp"
#include "glad/glad.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

VAO::VAO(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices) :
 vertices_(vertices), indices_(indices), nVertices_(nVertices), nIndices_(nIndices) {
    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // set up vertex buffer
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices * 12, vertices, GL_STATIC_DRAW);

    const GLsizei vertexStride = 12 * sizeof(float);

    // how to use the 12-D vertices (x,y,z,r,g,b,a,s,t,nx,ny,nz), and use currently bound VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexStride, (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)(7 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexStride, (void*)(9 * sizeof(float)));

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
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}

void VAO::render(){
    // setup vertex array object
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // submit the draw call to the GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glDrawElements(GL_TRIANGLES, nIndices_, GL_UNSIGNED_INT, NULL);

    // cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}

VAO::~VAO(){
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ibo_);
    glDeleteVertexArrays(1, &vao_);
}

/**
 * This function will attempt to parse a PLY file representing a model.
 * 
 * @param modelFilename char* representing filename of model
 * @return a pointer to a VAO loaded from the specified file
 **/
VAO* loadVAOfromPLY(const char *modelFilename){
    std::ifstream in(modelFilename);
    if(!in){
        std::ostringstream oss;
        oss << "Error in opening Model file \"" << modelFilename << "\"";
        throw std::invalid_argument(oss.str());
    }

    std::vector<float> vertices;
    std::vector<unsigned> indices;
    int failed = 0, n8 =0 , n4 = 0, n3 = 0,n=0;
    for(std::string line; std::getline(in, line);){
        float x, y, z, nx, ny, nz, s, t;
        int matches = sscanf(line.c_str(), "%f %f %f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz, &s, &t);
        if(matches == 8){
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(1);
            vertices.push_back(1);
            vertices.push_back(1);
            vertices.push_back(1);
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            n8++;
        }else if(matches == 4 && x == 3){
            indices.push_back(y);
            indices.push_back(z);
            indices.push_back(nx);
            n4++;
        }
        #ifndef NO_SUPER_MEGA_HACK
        else if(matches == 3){
            double r = getRandomNormal() / 10.0;
            double g = getRandomNormal() / 8.0;
            double b = getRandomNormal() / 3.0;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);
            vertices.push_back(1);
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(r); // W A C K Y
            vertices.push_back(g);
            vertices.push_back(b);
            n3++;
        }else{
            failed++;
            std::cerr << line << std::endl;
        }
        n++;
        #endif
    }
    #ifndef NO_SUPER_MEGA_HACK
    std::cout << failed << " lines failed, " << n4 << " lines had 4 elements, " << n3 << " lines had 3 elements, and "
     << n8 << "lines had 8 elements out of " << n << " lines!" << std::endl; 
    #endif
    std::cout << "\"" << modelFilename << "\" loaded successfully!" << std::endl;
    
    return new VAO(vertices.data(), indices.data(), vertices.size()/12, indices.size());
}