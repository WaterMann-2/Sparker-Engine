#ifndef GUI_CPP

#define GUI_CPP

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <iostream>
#include <string>

#include "GameObject/Mesh.h"

class gui {

public:

	ImGuiIO* IO;

	gui(GLFWwindow* window);

	void guiTerminate();

	void BeginFrame();

	void EndFrame();

	void MeshInfo(Mesh inputMesh);

	/*
	void NewGuiWindow(const char* windowName);

	void EndGuiWindow();*/

private:


};


#endif