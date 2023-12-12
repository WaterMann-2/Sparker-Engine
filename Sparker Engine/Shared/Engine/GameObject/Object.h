
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


	void componentEarlyUpdate();
	void componentUpdate();
	void componentLateUpdate();

private:
	std::vector<Component*> components;


};

#endif // !OBJECT_H
