#ifndef LIGHT_H
#define LIGHT_H
#include "entity.hpp"
#include "glm/glm.hpp"

extern Model *defaultLightModel;
extern Texture *defaultLightTexture;

class Light : public Entity{
    public:
        Light(glm::vec3 color, float intensity);
        Light();
    private:
        glm::vec3 color_;
        float intensity_;
};

#endif