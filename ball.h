#pragma once
#include "cw\drawableObj.h"

class ball :public drawableObj{
public:
	ball(glm::vec2 cooords, texture& t) :drawableObj({ cooords.x,cooords.y,15,15 }, t, {130,140,200,255}) {
		
	};
	float angle = 0.0f;
	void update();
};