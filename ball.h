#pragma once
#include "cw\drawableObj.h"
#include "cw\things.h"

class ball {//r = 7.5
public:
	ball() = default;
	ball(const glm::vec2 cooords,const texture& t):pos(cooords),m_t(t) {
		
	};

	//ball operator=(const ball&) = default;

	void changeAngle(double newAngle);
	void draw(drawRenderer&)const;
	//void update();
	//math::radians angle;
	float angle;
	glm::vec2 pos;
	void move() { pos += 6.0f*m_unitVec; };
	friend class gameMap;
	glm::vec2 m_unitVec;
private:
	
	texture m_t;
};



