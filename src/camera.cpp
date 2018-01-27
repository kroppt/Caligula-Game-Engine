#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 lookAt){
    this->position = position;
    this->lookAt = lookAt;
}


glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(position, lookAt, UP);
}
