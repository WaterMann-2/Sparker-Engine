#ifndef TRANSFORM_H

#define TRANSFORM_H

#include <glm/glm.hpp>
#include "GameObject/Component.h"

class Transform {

public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform() {
		glm::vec3 zero = glm::vec3(0.0f, 0.0f, 0.0f);
		position = zero;
		rotation = zero;
		scale =    zero;
	}
	
};
#endif // !TRANSFORM_H
