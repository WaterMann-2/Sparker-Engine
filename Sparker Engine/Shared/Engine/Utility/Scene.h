
#ifndef SCENE_H

#define SCENE_H

#include <iostream>
#include <string>
#include <vector>

#include "GameObject/Object.h"

class Scene {

public: 

	Time* sceneTime;

	Scene();

	void BindObject(Object* object);
	
	void EarlyTick();

	void OnTick();

	void LateTick();
	
	
private:
	std::string SceneName = "Default";

	std::vector<Object*> sceneObjects;


};

#endif // !SCENE_H
