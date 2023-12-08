#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "GameObject/Component.h"
#include "Object.h"

template Component* Object::GetComponent<Component>();

template void Object::AddComponent<Component>(Component* component);

template void Object::RemoveComponent<Component>(Component* component);

template <typename T> 
T* Object::GetComponent() {
	for (Component* component : components) {
		if (typeid(T) == typeid(*component)) {
			return dynamic_cast<T*>(component);
		}
	}
	return nullptr;
}

template <typename T>
void Object::AddComponent(T* component) {
	/*if (typeid(T) == typeid(component)) {
		std::cout<< "[ERROR]: Component of type \"" << typeid(T) << "\" already exists in \"" << "wow" << "\"" << std::endl;
	}*/
	components.push_back(component);
}

template <typename T>
void Object::RemoveComponent(T* component) {
	auto it = find(components.begin(), components.end(), component);
	if (it != components.end()) {
		components.erase(it);
	}
}