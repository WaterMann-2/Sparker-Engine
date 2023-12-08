#ifndef WINDOW_H

#define WINDOW_H

#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

#include <stb/stb_image.h>



class Window {

public:
	string Name;

	GLFWwindow* window;

	float lastFrameTime = 0.0f, deltaTime = 0.0f;
	
	glm::vec2 mousePosition = glm::vec2(0.0f, 0.0f), mouseDelta = glm::vec2(0.0f, 0.0f);
	
	Window(glm::vec2 StartSize, const char* WindowName) {
		//Window Init
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		Name = std::string(WindowName);

		window = glfwCreateWindow(StartSize.x, StartSize.y, WindowName, NULL, NULL);
		if (window == NULL) {
			std::cout << "[ERROR]: Window " << WindowName << " not succesfully created" << endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);

	}

	void setInputKeys(vector<int> newInputKeys) {
		inputKeys = newInputKeys;
		inputKeysPressed.resize(inputKeys.size(), false);
		std::fill(inputKeysPressed.begin(), inputKeysPressed.end(), false);
	}

	void processKeys() {
		for (unsigned int i = 0; i < inputKeys.size(); i++) {
			char* currentKey = &inputKeysPressed[i];
			if (glfwGetKey(window, inputKeys[i])) {
				*currentKey = true;
				continue;
			}
			*currentKey = false;
			
		}
	}

	void processMouse() {

		for(unsigned int i = 0; i < 4; i ++){
			char* currentMouse = &mouseButtonsPressed[i];
			if (glfwGetMouseButton(window, i)) {
				*currentMouse = true;
				continue;
			}
			*currentMouse = false;
		}
	}

	bool getMouseButton(unsigned int MouseButton) {
		if (MouseButton < 5) {
			return mouseButtonsPressed[MouseButton];
		}
		return false;
	}



private:
	vector<int> inputKeys;
	vector<char> inputKeysPressed;
	char mouseButtonsPressed[5] = { 0, 0, 0, 0, 0 };

};


#endif

