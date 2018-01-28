#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <unordered_map>
#include "model.hpp"
#include "texture.hpp"

class ResourceManager{
    public:
        Model* loadModel(char *modelFilename);
        Texture* loadTexture(char *textureFilename);
    private:
        std::unordered_map<char*, Model*> modelMap_;
        std::unordered_map<char*, Texture*> textureMap_;
};

#endif