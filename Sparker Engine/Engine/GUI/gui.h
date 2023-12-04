#ifndef GUI_CPP

#define GUI_CPP

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

#include "stb_image.h"

class gui {

public:

	ImGuiIO* IO;

	gui(GLFWwindow* window);

	void guiTerminate();

	void BeginFrame();

	void EndFrame();

private:


};


#endif