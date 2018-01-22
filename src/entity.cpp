#include "entity.h"
#include "vao.h"

Entity::Entity(VAO *vao, Texture *texture) : vao_(vao), texture_(texture) { }

/**
 * This constructor is merely for laziness, would not be used in practice as it
 * loads the same model and texture into memory multiple times. As such, there is
 * an obvious memory leak to go along with it.
 **/ 
Entity::Entity(const char *modelFilename, const char *textureFilename){
    vao_ = loadVAOfromPLY(modelFilename);
    texture_ = new Texture(textureFilename);
}

void Entity::render(float alpha){
    // TODO implement positioning and rotation of entity
    texture_->bind();
    vao_->render();
    texture_->unbind();
}
