#pragma once
#include "cw\drawableObj.h"
#include "cw\Rectangle.h"
class block:public Rectangle{ 
public:
	block() = default;
	block(glm::vec2 pos, int start) :Rectangle(glm::vec4(pos.x, pos.y, 30.0f, 20.0f), {100,140,200,255}):m_current(start) {};
private:
	int m_current = 0;
};