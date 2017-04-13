#pragma once
#include "cw\drawableObj.h"

class ball {
public:
	ball(const glm::vec2 cooords,const texture& t):pos(cooords),m_t(t) {
		
	};

	void changeAngle(float newAngle);
	void draw(drawRenderer&);
	//void update();
	float angle;
	glm::vec2 pos;
	void move() { pos += m_unitVec; };
	friend class gameMap;
private:
	glm::vec2 m_unitVec;
	const texture& m_t;
};



