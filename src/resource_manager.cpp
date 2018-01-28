#include "resource_manager.hpp"
#include <unordered_map>
#include "model.hpp"

Model* ResourceManager::loadModel(char *modelFilename){
    if(modelMap_.find(modelFilename) == modelMap_.end()){
        return (modelMap_[modelFilename] = loadModelfromPLY(modelFilename));
    }else{
        return modelMap_.at(modelFilename);
    }
}

Texture* ResourceManager::loadTexture(char *textureFilename){
    if(textureMap_.find(textureFilename) == textureMap_.end()){
        return (textureMap_[textureFilename] = new Texture(textureFilename));
    }else{
        return textureMap_.at(textureFilename);
    }
}
