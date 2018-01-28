#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "glad/glad.h"

const glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);

#define PITCH_LIMIT 0.01f
class Camera{
	public:
		Camera(glm::vec3 position, glm::vec3 lookAt, float aspect);
		void update(void);
		glm::mat4 getViewMatrix();
		void UpdateLook(float dx, float dy);
		void Move(float dForward, float dWright, float dUp);
		
		// camera setup
		void InitUniforms(GLuint shaderID);
		void UploadUniforms(GLuint shaderID);
		glm::vec3 position;
		glm::vec3 lookAt;
		glm::vec3 right, forwards;

		//
		//float yaw, pitch, roll;

		float phi, theta;

	private:
		GLint viewLocation;
		GLint projectionLocation;
		GLint vpLocation;
		//
		glm::mat4 projection;
		glm::mat4 view;
};

#endif
