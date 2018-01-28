#ifndef ENTITY_H
#define ENTITY_H
#include "model.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define INV_UNIFORM 0xFFFFFFFF
class Entity{
    public:
        Entity(Model *model, Texture *texture);
        /**
         * This constructor is merely for laziness, would not be used in practice as it
         * loads the same model and texture into memory multiple times. As such, there is
         * an obvious memory leak to go along with it.
         **/ 
        Entity(const char *modelFilename, const char *textureFilename);
        void render(float alpha, uint uniformLocation);

        glm::vec3 position, velocity;
        float yaw, pitch, roll, scale;
        Texture *texture_;
    private:
        Model *model_;

};

#endif