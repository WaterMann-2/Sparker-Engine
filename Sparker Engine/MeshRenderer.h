#ifndef MESHRENDERER_H

#define MESHRENDERER_H

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <glfw3.h>

#include "Component.h"

class MeshRenderer : public Component {

public:
	
	const char* componentName;
	static const int componentID = 1;


	MeshRenderer() {
		componentName = "Mesh Renderer";

		
	}


private:

};

#endif
