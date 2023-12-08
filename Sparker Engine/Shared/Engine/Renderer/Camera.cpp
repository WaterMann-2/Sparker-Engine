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
#include "Renderer/Camera.h"


Camera::Camera() {
	projection = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::AssignWindow(GLFWwindow* window) {
	int WinWidth, WinHeight;

	glfwGetWindowSize(window, &WinWidth, &WinHeight);

	UpdateProjection(WinWidth, WinHeight);
}

void Camera::UpdateCamera() {
	glm::vec3 direction;

	direction.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	direction.y = sin(glm::radians(transform.rotation.x));
	direction.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

	cameraFront = glm::normalize(direction);
	view = glm::lookAt(transform.position, transform.position + cameraFront, cameraUp);
}

void Camera::UpdateProjection(int width, int height) {
	float aspectRatio = static_cast<float>(width) / height;
	std::cout << "New Ratio: " << aspectRatio << std::endl;
	projection = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, FarClipPlane);
}
