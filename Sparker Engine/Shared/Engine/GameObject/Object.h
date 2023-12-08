#ifndef OBJECT_H

#define OBJECT_H

#include <iostream>
#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <string>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "GameObject/Component.h"

#include "Renderer/Shader.h"
#include "Utility/Transform.h"
#include "Renderer/Camera.h"
#include "GameObject/Model.h"

class Object {

public:
	template <typename T> T* GetComponent() {
		for (Component* component : components) {
			if (typeid(T) == typeid(*component)) {
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}

	template <typename T> void AddComponent(T* component) {
		components.push_back(component);
	}

	template <typename T> void RemoveComponent(T* component) {
		components.erase(component);
	}

	Transform transform;


private:
	std::vector<Component*> components;
	
	
};


#endif // !OBJECT_H
