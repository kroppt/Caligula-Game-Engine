#include "model.h"
#include "vao.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

Model::Model(VAO *vao, Texture *texture) : vao_(vao), texture_(texture) { }

Model::Model(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, Texture *texture) : texture_(texture) {

}

Model::Model(VAO *vao, const char *textureFilename, GLenum target): vao_(vao){

}

Model::Model(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, const char *textureFilename, GLenum target){

}

Model::Model(const char *modelFilename, Texture *texture) : texture_(texture) {

}

Model::Model(const char *modelFilename, const char *textureFilename, GLenum target){

}

/**
 * 
 * Temporary, testing
 * 
 **/
VAO* loadVAOfromOBJ(const char *modelFilename){
    FILE *fp = fopen(modelFilename, "r");
    if(fp == NULL){
        std::ostringstream oss;
        oss << "Error in opening model file \"" << modelFilename << "\"";
        throw std::invalid_argument(oss.str());
    }

    std::vector<float> vertices;
    std::vector<float> tcoords;
    std::vector<unsigned> indices;

    while(true){
        // sloppy assumption
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(fp, "%s", lineHeader);
        if(res == EOF) break;
        if(strcmp(lineHeader, "v") == 0){
            float x, y, z;
            fscanf(fp, "%f %f %f\n", &x, &y, &z);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            // TEST: for color, use white opaque
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
        }else if(strcmp(lineHeader, "vt") == 0){
            float s, t;
            fscanf(fp, "%f %f\n", &s, &t);
            tcoords.push_back(s);
            tcoords.push_back(t);
        }else if(strcmp(lineHeader, "f") == 0){
            // xyz, triangle indices
            unsigned vxi, vyi, vzi, uvxi, uvyi, uvzi, nxi, nyi, nzi;
            fscanf(fp, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vxi, &uvxi, &nxi, &vyi, &uvyi, &nyi ,&vzi, &uvzi, &nzi);
            indices.push_back(vxi);
            indices.push_back(vyi);
            indices.push_back(vzi);
        }

    }

    std::cout << "\"" << modelFilename << "\" loaded successfully!" << std::endl;
    
    return new VAO(vertices.data(), indices.data(), tcoords.data(), vertices.size(), indices.size(), tcoords.size());
}