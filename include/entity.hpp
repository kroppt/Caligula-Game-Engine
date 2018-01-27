#ifndef ENTITY_H
#define ENTITY_H
#include "vao.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity{
    public:
        Entity(VAO *vao, Texture *texture);
        /**
         * This constructor is merely for laziness, would not be used in practice as it
         * loads the same model and texture into memory multiple times. As such, there is
         * an obvious memory leak to go along with it.
         **/ 
        Entity(const char *modelFilename, const char *textureFilename);
        void render(float alpha, uint uniformLocation);

        glm::vec3 position, velocity;
        float yaw, pitch, roll, scale;
    private:
        VAO *vao_;
        Texture *texture_;

};

#endif