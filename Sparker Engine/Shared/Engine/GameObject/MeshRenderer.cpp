#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject/Component.h"
#include "Utility/MaterialManager.h"
#include "GameObject/MeshRenderer.h"


MeshRenderer::MeshRenderer() {
	
}

void MeshRenderer::EarlyFrame() {
	//for (unsigned int i = 0; i < Meshes.size(); i++) Meshes[i]->Draw();
}
