#include "ball.h"
#include <cmath>

void ball::changeAngle(float newAngle){
	angle.angle = newAngle;

	m_unitVec = { cos(angle),sin(angle) };
}

void ball::draw(drawRenderer& r)const {
	r.draw({ pos.x-7.5,pos.y-7.5,15,15 }, fullPicUV, m_t.id, {0,0,0,255},1.0f);
}