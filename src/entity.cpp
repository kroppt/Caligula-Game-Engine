#include "nus/linalg.h"
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
    position_.x = 0.1f; position_.y = 0.1f; position_.z = 0.1f; position_.w = 1.0f;
    rotation_.x = 1; rotation_.y = .0f; rotation_.z = .0f; rotation_.w = 0;
}

void Entity::render(float alpha, uint uniformLocation){
    // TODO implement positioning and rotation of entity
    mat4 mat, rot, res;
    //
    mat4_set_translate(&mat, position_);
    //mat4_set_identity(&)
    vec4 rotat = vec4_norm(rotation_);
    mat4_set_rotation(&rot, rotat);

    mat4_set_mul(&res, mat, rot);
    //mat4_set_identity(&res);
    float *f = (float*)&res.m;
    glUniformMatrix4fv(uniformLocation, 1, false, f);

    texture_->bind();
    vao_->render();
    texture_->unbind();
}
