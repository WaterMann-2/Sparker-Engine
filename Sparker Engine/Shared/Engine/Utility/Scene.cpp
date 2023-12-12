
#include <iostream>
#include <string>
#include <vector>

#include "GameObject/Object.h"
#include "Utility/Time.h"
#include "Utility/Scene.h"

Scene::Scene() {

}

void  Scene::BindObject(Object* object) {
	sceneObjects.push_back(object);
}


void Scene::EarlyTick() {
	for (Object* object : sceneObjects) {
		object->componentEarlyUpdate();
	}
}

void Scene::OnTick() {
	for (Object* object : sceneObjects) {
		object->componentUpdate();
	}
}

void Scene::LateTick() {
	for (Object* object : sceneObjects) {
		object->componentLateUpdate();
	}
}
