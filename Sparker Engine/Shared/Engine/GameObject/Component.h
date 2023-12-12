
#ifndef COMPONENT_H

#define COMPONENT_H

#include <iostream>

class Component {

public:

	virtual ~Component() = default;

	/**
	Called early once every frame
	*/
	virtual void EarlyFrame();

	/**
	Called once every frame
	*/
	virtual void OnFrame();

	/**
	Called once late every frame
	*/
	virtual void LateFrame();
};

#include "GameObject/Component.cpp"
#endif // !COMPONENT_H
