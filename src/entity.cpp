#include "entity.h"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "vao.h"

Entity::Entity(VAO *vao, Texture *texture) : vao_(vao), texture_(texture) {}

/**
 * This constructor is merely for laziness, would not be used in practice as it
 * loads the same model and texture into memory multiple times. As such, there is
 * an obvious memory leak to go along with it.
 **/ 
Entity::Entity(const char *modelFilename, const char *textureFilename){
    vao_ = loadVAOfromPLY(modelFilename);
    texture_ = new Texture(textureFilename);
    position.x = 0.0f; position.y = -0.1f; position.z = -0.9f;
    yaw = 0; pitch = 0; roll = 0;
}

void Entity::render(float alpha, uint uniformLocation){
    // TODO implement positioning and rotation of entity
    glm::mat4 translation_matrix, rotation_matrix, result_matrix;

    translation_matrix = glm::translate(translation_matrix, position);
    rotation_matrix = glm::yawPitchRoll(yaw, pitch, roll);
    result_matrix = translation_matrix * rotation_matrix;
    glUniformMatrix4fv(uniformLocation, 1, false, &result_matrix[0][0]);

    texture_->bind();
    vao_->render();
    texture_->unbind();
}
