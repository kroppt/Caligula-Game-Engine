#include "entity.h"
#include "vao.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

Entity::Entity(VAO *vao, Texture *texture) : vao_(vao), texture_(texture) { }

Entity::Entity(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, Texture *texture) : texture_(texture) {

}

Entity::Entity(VAO *vao, const char *textureFilename, GLenum target): vao_(vao){

}

Entity::Entity(float *vertices, unsigned *indices, size_t nVertices, size_t nIndices, const char *textureFilename, GLenum target){

}

Entity::Entity(const char *ModelFilename, Texture *texture) : texture_(texture) {

}

Entity::Entity(const char *ModelFilename, const char *textureFilename, GLenum target){

}

/**
 * 
 * Temporary, testing
 * 
 **/
VAO* loadVAOfromOBJ(const char *ModelFilename){
    //XXX GET RID OF THIS
    FILE *fp = fopen(ModelFilename, "r");
    if(fp == NULL){
        std::ostringstream oss;
        oss << "Error in opening Model file \"" << ModelFilename << "\"";
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
            //

        }else if(strcmp(lineHeader, "vt") == 0){
            float s, t;
            fscanf(fp, "%f %f\n", &s, &t);
            //vertices.push_back(s);
            //vertices.push_back(t);
        }else if(strcmp(lineHeader, "f") == 0){
            // xyz, triangle indices
            unsigned vxi, vyi, vzi, uvxi, uvyi, uvzi, nxi, nyi, nzi;
            fscanf(fp, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vxi, &uvxi, &nxi, &vyi, &uvyi, &nyi ,&vzi, &uvzi, &nzi);
            indices.push_back(vxi);
            indices.push_back(vyi);
            indices.push_back(vzi);
        }

    }

    std::cout << "\"" << ModelFilename << "\" loaded successfully!" << std::endl;
    
    return new VAO(vertices.data(), indices.data(), vertices.size(), indices.size());
}