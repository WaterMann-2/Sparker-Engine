
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <iostream>
#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include <stb/stb_image.h>
#include "gui.h"
#include "GameObject/Mesh.h"
#include "Utility/Window.h"



gui::gui(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& localIO = ImGui::GetIO(); (void)localIO;
	IO = &localIO;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void gui::guiTerminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void gui::EndFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui::WindowInformation(Window window) {
	Window& currentWindow = window;
	std::string frameTimeStr;

	if (currentWindow.deltaTime * 1000 < 0.0f) {
		frameTimeStr = "<0ms";
		
	}
	else {
		frameTimeStr = std::to_string((int)(currentWindow.deltaTime * 1000)) + "ms";
	}

	ImGui::Begin("Window Information");
	ImGui::Text(("Window: " + window.Name).c_str());
	ImGui::Text(("Last frame time: " + frameTimeStr).c_str());
	ImGui::End();
}

/*
void gui::NewGuiWindow(const char* windowName) {
	ImGui::Begin(windowName);
}

void gui::EndGuiWindow() {
	ImGui::End();
}*/