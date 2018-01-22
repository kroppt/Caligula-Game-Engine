#ifndef ENTITY_H
#define ENTITY_H
#include "vao.h"
#include "texture.h"
#include "nus/linalg.h"

class Entity{
    public:
        Entity(VAO *vao, Texture *texture);
        /**
         * This constructor is merely for laziness, would not be used in practice as it
         * loads the same model and texture into memory multiple times. As such, there is
         * an obvious memory leak to go along with it.
         **/ 
        Entity(const char *modelFilename, const char *textureFilename);
        vec4 getPosition() { return position_; }
        vec4 getVelocity() { return velocity_; }
        vec4 getRotation() { return rotation_; } 
        vec4 getAngularVelocity() { return angularVelocity_; }
        void setPosition(vec4 position) { position_ = position; }
        void setVelocity(vec4 velocity) { velocity_ = velocity; }
        void setRotation(vec4 rotation) { rotation_ = rotation; }
        void setAngularVelocity(vec4 angularVelocity) { angularVelocity_ = angularVelocity; }
        void render(float alpha);

    private:
        VAO *vao_;
        Texture *texture_;
        vec4 position_, velocity_, rotation_, angularVelocity_;

};

#endif