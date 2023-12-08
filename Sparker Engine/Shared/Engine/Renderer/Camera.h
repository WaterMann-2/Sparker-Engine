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

	Transform transform;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	const char* name = "Camera";

	float FOV = 90.0f;
	float FarClipPlane = 1000.0f;

	
	Camera();
	void AssignWindow(GLFWwindow* window);
	void UpdateCamera();
	void UpdateProjection(int width, int height);


private:
	
	

};


#endif
