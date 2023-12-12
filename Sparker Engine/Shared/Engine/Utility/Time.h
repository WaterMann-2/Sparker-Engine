#ifndef TIME_H

#define TIME_H

#include <iostream>
#include "glfw3/glfw3.h"

class Time {
	
public:

	void CalcTime() {
		FrameTime = glfwGetTime() - LastFrame;
		LastFrame = FrameTime + LastFrame;
	}

	float deltaTime() {
		return FrameTime;
	}
	
private:

	float FrameTime = 0.0f;

	float LastFrame = 0.0f;
};

#endif // !TIME_H
