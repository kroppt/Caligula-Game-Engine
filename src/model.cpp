#include "model.h"
#include "vao.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

VAO loadVAOfromOBJ(const char *modelFilename){
    FILE *fp = fopen(modelFilename, "r");
    if(fp == NULL){
        std::ostringstream oss;
        oss << "Error in opening model file \"" << modelFilename << "\"";
        throw std::invalid_argument(oss.str());
    }

    std::vector<float> vertices;
    std::vector<unsigned> indices;

    while(true){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(fp, "%s", lineHeader);
        if (res == EOF) break;
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
    }

}