#include "entity.h"
#include "vao.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

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
VAO* loadVAOfromPLY(const char *ModelFilename){
    std::ifstream in(ModelFilename);
    if(!in){
        std::ostringstream oss;
        oss << "Error in opening Model file \"" << ModelFilename << "\"";
        throw std::invalid_argument(oss.str());
    }

    std::vector<float> vertices;
    std::vector<unsigned> indices;

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
            vertices.push_back(s);
            vertices.push_back(t);
        }else if(matches == 4 && x == 3){
            indices.push_back(y);
            indices.push_back(z);
            indices.push_back(nx);
        }
    }

    std::cout << "\"" << ModelFilename << "\" loaded successfully!" << std::endl;
    
    return new VAO(vertices.data(), indices.data(), vertices.size(), indices.size());
}