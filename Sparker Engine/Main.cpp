
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Shader.h"
#include "stb_image.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "Window.h"

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

ImGuiIO* globalIO;

void processInput(GLFWwindow* window);
void mouse_delta_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_entered_callback(GLFWwindow* window, int entered);
unsigned int loadTexture(char const* path);


int main() {

	//Window Creation
	Window mainWindow(windowStartingSize, "Sparker Engine");
	GLFWwindow* window = mainWindow.window;

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

	stbi_set_flip_vertically_on_load(true);

	//global opengl state
	glEnable(GL_DEPTH_TEST);

	//build and compile shaders
	Shader backpackShader("model_loading.vs", "model_loading.frag");

	//Load Models
	Model backpackModel("backpack/backpack.obj");

	//Camera stuff
	windowSize = glm::vec2(windowStartingSize.x, windowStartingSize.y);
	Camera cam("Main", window, 90.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	globalIO = &io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Use Shaders
		backpackShader.use();

		//Camera Update
		cam.UpdateProjection(windowSize.x, windowSize.y);

		cam.transform.position = cameraPos;
		cam.transform.rotation = glm::vec3(pitch, yaw, 0.0f);
		cameraFront = cam.cameraFront;

		cam.UpdateCamera();

		glm::mat4 projection = cam.projection;
		glm::mat4 view = cam.view;

		//Update Shader Projection
		backpackShader.setMat4("projection", projection);
		backpackShader.setMat4("view", view);

		//Render Models
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		backpackShader.setMat4("model", model);
		backpackModel.Draw(backpackShader);


		ImGui::Begin("Shitass Nuts");
		ImGui::Text("GO TO HELL!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//call events, buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


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

	cout << "x: " << rxpos << " y: " << rypos << endl;

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