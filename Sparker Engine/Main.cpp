#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <iostream>
#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <string>

#include "Renderer/Shader.h"
#include "Utility/Transform.h"
#include "Renderer/Camera.h"
#include "GameObject/Model.h"
#include "Utility/Window.h"

#include "GUI/gui.h"
#include "GameObject/MeshRenderer.h"
#include "GameObject/Object.h"

glm::vec2 windowStartingSize(1600, 1000);
glm::vec2 windowSize;

Camera cam;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastx = 400, lasty = 300;
float pitch = 0.0f, yaw = -90.0f;

glm::vec3& cameraPos = cam.transform.position;
glm::vec3& cameraFront = cam.cameraFront;
glm::vec3& cameraUp = cam.cameraUp;

bool firstmouse = true;
bool MouseEntered = false;

ImGuiIO* globalIO;

void processInput(GLFWwindow* window);
void mouse_delta_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_entered_callback(GLFWwindow* window, int entered);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	windowSize = glm::vec2(width, height);
	cam.UpdateProjection(width, height);
	glViewport(0, 0, width, height);
}

int main() {

	Object pogObject;
	MeshRenderer* rend = new MeshRenderer;
	pogObject.AddComponent(rend);

	MeshRenderer* rendRef = pogObject.GetComponent<MeshRenderer>();
	if (rendRef != NULL) {
		rendRef->SayHello();
	}

	//Window Creation
	Window mainWindow(windowStartingSize, "Sparker Engine");
	GLFWwindow*& window = mainWindow.window;

	//Load Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load Glad" << endl;
	}


	//global opengl state
	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);

	//Camera stuff
	cam.AssignWindow(window);

	//Gui
	gui basicGui(window);
	globalIO = basicGui.IO;

	int wwidth, wheight;

	while (!glfwWindowShouldClose(window)) {

		// Input Handling
		glfwSetCursorPosCallback(window, mouse_delta_callback);
		glfwSetCursorEnterCallback(window, mouse_entered_callback);
		processInput(window);

		//Frame Time Logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		mainWindow.deltaTime = deltaTime;

		//render loop
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GUI begin
		basicGui.BeginFrame();

		basicGui.WindowInformation(mainWindow);

		basicGui.EndFrame();

		//call events, buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	basicGui.guiTerminate();


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {

	ImGuiIO& io = *globalIO;
	
	const float cameraSpeed = 1.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstmouse = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && MouseEntered && !io.WantCaptureMouse) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
		
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	
}

void mouse_delta_callback(GLFWwindow* window, double xpos, double ypos) {

	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		return;
	}

	double rxpos, rypos;

	glfwGetCursorPos(window, &rxpos, &rypos);

	if (firstmouse) {
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}

	float xoffset = xpos - lastx;
	float yoffset = -ypos + lasty;

	lastx = xpos;
	lasty = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.5f) {
		pitch = 89.5f;
	}
	if (pitch < -89.5f) {
		pitch = -89.5f;
	}

}

void mouse_entered_callback(GLFWwindow* window, int entered) {

	if (entered) {
		MouseEntered = true;
		return;
	}

	if (!entered) {
		MouseEntered = false;
		firstmouse = true;
		return;
	}
}