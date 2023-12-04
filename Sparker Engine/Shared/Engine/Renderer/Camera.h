#ifndef CAMERA_H

#define CAMERA_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include "Utility/Transform.h"

class Camera {

public:

	glm::mat4 projection;
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	Transform transform;

	char* name;

	float FOV = 60.0f;
	float FarClipPlane = 1000.0f;

	
	Camera(const char* name, GLFWwindow* window, const float CameraFOV) {

		transform;

		FOV = CameraFOV;

		int WinWidth, WinHeight;

		glfwGetWindowSize(window, &WinWidth, &WinHeight);
		
		projection = glm::perspective(glm::radians(FOV), (float)WinWidth / (float)WinHeight, 0.1f, FarClipPlane);
	}
	 
	/**
	Used to update Position and Rotation
	*/
	void UpdateCamera() {
		glm::vec3 direction;

		direction.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		direction.y = sin(glm::radians(transform.rotation.x));
		direction.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

		cameraFront = glm::normalize(direction);
		view = glm::lookAt(transform.position, transform.position + cameraFront, cameraUp);
	}

	/**
	Used to modify camera lens (ex. fov)
	*/
	void UpdateProjection(int width, int height) {

		projection = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, FarClipPlane);
		//std::cout << "my ass dividing " << width << " by " << height << endl;
	}


private:
	
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

};


#endif
