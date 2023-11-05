#ifndef TRANSFORM_H

#define TRANSFORM_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <glfw3.h>

/**
Contains position, rotation, and scale of an object in 3D space
*/
class Transform {

public:

	/**
	 The Position of the object as a glm vector3
	*/
	glm::vec3 position;

	/**
	 The Position of the object as a glm vector3
	*/
	glm::vec3 rotation;

	/**
	 The Position of the object as a glm vector3
	*/
	glm::vec3 scale;

	static glm::vec3 VectorZero;

	Transform(){
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale    = glm::vec3(1.0f, 1.0f, 1.0f);
	}

};

#endif

