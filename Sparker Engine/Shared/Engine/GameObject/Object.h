#pragma once

#ifndef OBJECT_H

#define OBJECT_H

#include <vector>

#include "Utility/Transform.h"

class Object {

public:
	std::string Name = "Default";

	template <typename T>
	void AddComponent(T* component);

	template <typename T>
	void RemoveComponent(T* component);

	template <typename T>
	 T* GetComponent();


	Transform transform;


private:
	std::vector<Component*> components;
	
	
};

#include "GameObject/Object.cpp"
#endif // !OBJECT_H
