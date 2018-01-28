#include "entity.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "model.hpp"

Entity::Entity(Model *model, Texture *texture) {
    model_ = model;
    texture_ = texture;
    scale = 1.0f;
    yaw = 0; pitch = 0; roll = 0;
}

/**
 * This constructor is merely for laziness, would not be used in practice as it
 * loads the same model and texture into memory multiple times. As such, there is
 * an obvious memory leak to go along with it.
 **/ 
Entity::Entity(const char *modelFilename, const char *textureFilename){
    model_ = loadModelfromPLY(modelFilename);
    texture_ = new Texture(textureFilename);
    position = glm::vec3(0,0,0);
    yaw = 0; pitch = 0; roll = 0;
    scale = 1.0f;
}

void Entity::render(float alpha, uint uniformLocation){
    if(uniformLocation != INV_UNIFORM){
        glm::mat4 translation_matrix, rotation_matrix, result_matrix, scale_matrix;
        translation_matrix = glm::translate(translation_matrix, position + alpha * velocity);
        rotation_matrix = glm::yawPitchRoll(yaw, pitch, roll);
        scale_matrix = glm::scale(scale_matrix, glm::vec3(scale, scale,scale));
        result_matrix = translation_matrix * rotation_matrix * scale_matrix;
        glUniformMatrix4fv(uniformLocation, 1, false, &result_matrix[0][0]);
    }
    texture_->bind();
    model_->render();
    texture_->unbind();
}
