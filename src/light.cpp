#include "light.hpp"
#include <glm/glm.hpp>

Model *defaultLightModel = NULL;
Texture *defaultLightTexture = NULL;

Light::Light(glm::vec3 color, float intensity) : Entity(defaultLightModel, defaultLightTexture) {
    color_ = color;
    intensity_ = intensity;
}

Light::Light() : Entity(defaultLightModel, defaultLightTexture){
    color_ = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_ = 1.0f;
}