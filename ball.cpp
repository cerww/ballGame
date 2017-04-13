#include "ball.h"
#include <cmath>

void ball::changeAngle(float newAngle){
	angle = newAngle;

	m_unitVec = { cos(newAngle),sin(newAngle) };
}

void ball::draw(drawRenderer& r) {
	r.draw({ pos.x,pos.y,15,15 }, fullPicUV, m_t.id, {0,0,0,255},1.0f);
}