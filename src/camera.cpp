#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <math.h>
#define ZFAR 1000.0f
Camera::Camera(glm::vec3 position, float aspect){
    this->position = position;
    this->projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, ZFAR);
    phi = M_PI_2;
    theta = M_PI;
    this->update();
}

void Camera::update(void){
    forwards = glm::vec3(sinf(phi) * cosf(theta), cosf(phi), sinf(phi) * sinf(theta));
    lookAt = forwards + position;
    right = glm::normalize(glm::cross(forwards, UP));
    view = getViewMatrix();
}

void Camera::UpdateLook(float dx, float dy){
    phi = glm::clamp(phi + dy / 300.0f, PITCH_LIMIT, ((float)M_PI) - PITCH_LIMIT);
    theta += dx / 300.0f;
}

void Camera::Move(float dForward, float dWright, float dUp){
    position += dForward * forwards;
    position += dWright * right;
    position += dUp * UP;
}

void Camera::InitUniforms(GLuint shaderID){
    viewLocation  = glGetUniformLocation(shaderID, "view" );
    projectionLocation  = glGetUniformLocation(shaderID, "projection" );
    vpLocation = glGetUniformLocation(shaderID, "vp");
}

void Camera::UploadUniforms(GLuint shaderID){
    glUseProgram(shaderID);
    glm::mat4 pv = projection * view;
    glUniformMatrix4fv(vpLocation, 1, false, &pv[0][0]);
    glUniformMatrix4fv(viewLocation, 1, false, &view[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, false, &projection[0][0]);
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(position, lookAt, UP);
}
