#pragma once
#include "cw\drawableObj.h"
#include "cw\Rectangle.h"
class block{ 
public:
	block() = default;
	void draw(drawRenderer&)const;
	glm::ivec2 m_pos;
	int m_current = 0;
private:

};