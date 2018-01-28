#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

const glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);

class Camera{
	public:
		Camera(glm::vec3 position, glm::vec3 lookAt);
		glm::mat4 getViewMatrix();
		glm::vec3 position;
		glm::vec3 lookAt;

		//
		float yaw, pitch, roll;
		
};

#endif
