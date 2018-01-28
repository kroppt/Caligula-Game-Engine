#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <unordered_map>
#include "model.hpp"
#include "texture.hpp"

class ResourceManager{
    public:
        Model* loadModel(const char *modelFilename);
        Texture* loadTexture(const char *textureFilename);
    private:
        std::unordered_map<const char*, Model*> modelMap_;
        std::unordered_map<const char*, Texture*> textureMap_;
};

#endif