
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Model.h"

glm::vec2 windowSize;
glm::vec2 oldSize;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	oldSize = windowSize;
	windowSize = glm::vec2(width, height);
	glViewport(0, 0, width, height);

}

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


glm::vec2 windowStartingSize(1600, 1000);


float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastx = 400, lasty = 300;
float pitch = 0.0f, yaw = -90.0f;

bool firstmouse = true;
bool MouseEntered = false;

void processInput(GLFWwindow* window);
void mouse_delta_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_entered_callback(GLFWwindow* window, int entered);
unsigned int loadTexture(char const* path);

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
};

int main() {

	//Initilize and Configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window Creation
	GLFWwindow* window = glfwCreateWindow(windowStartingSize.x, windowStartingSize.y, "Shitass Nuts", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	//Load Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load Glad" << endl;
	}

	//global opengl state
	glEnable(GL_DEPTH_TEST);

	//Model Import

	Model backpackModel("C:/Users/robsc/Downloads/backpack/backpack.obj");

	//Camera stuff

	windowSize = glm::vec2(windowStartingSize.x, windowStartingSize.y);
	Camera cam("Main", window, 90.0f);

	//transformations
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection;

	float angle = 0;


	while (!glfwWindowShouldClose(window)) {

		//Frame Time Logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		//input
		glfwSetCursorPosCallback(window, mouse_delta_callback);
		glfwSetCursorEnterCallback(window, mouse_entered_callback);
		processInput(window);

		//render loop
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		backpackModel.Draw();

		//Camera Update
		cam.UpdateProjection(windowSize.x, windowSize.y);

		cam.transform.position = cameraPos;
		cam.transform.rotation = glm::vec3(pitch, yaw, 0.0f);
		cameraFront = cam.cameraFront;
		
		cam.UpdateCamera();
		
		glm::mat4 projection = cam.projection;
		glm::mat4 view = cam.view;
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		
		//World transformationns
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);


		//Render cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Render lamp
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);

		//Transform lamp
		model = glm::mat4(1.0);
		model = glm::translate(model, lightTransform.position);
		model = glm::scale(model, glm::vec3(0.2f));

		lightCubeShader.setMat4("model", model);

		//Draw Light Cube
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//call events, buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	
	const float cameraSpeed = 1.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstmouse = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && MouseEntered) {
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

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		std::cout << stbi_failure_reason() << endl; 
		stbi_image_free(data);
	}

	return textureID;
}