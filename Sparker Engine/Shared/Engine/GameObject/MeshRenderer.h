#ifndef MESHRENDERER_H

#define MESHRENDERER_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject/Component.h"

class MeshRenderer : public Component {
public:
	void SayHello() {
		std::cout << "OH MY GAWWSH HAIIII!" << std::endl;
	}

};
#endif // !MESHRENDERER_H
