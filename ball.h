#pragma once
#include "cw\drawableObj.h"
#include "cw\things.h"

class ball {
public:
	ball() = default;
	ball(const glm::vec2 cooords,const texture& t):pos(cooords),m_t(t) {
		
	};

	void changeAngle(float newAngle);
	void draw(drawRenderer&)const;
	//void update();
	math::radians angle;
	glm::vec2 pos;
	void move() { pos += m_unitVec; };
	friend class gameMap;
	glm::vec2 m_unitVec;
private:
	
	texture m_t;
};



