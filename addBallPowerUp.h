#pragma once
#include <glm\glm.hpp>
#include "ball.h"

class addBallPowerUp {//r = 8
public:
	addBallPowerUp() = default;
	addBallPowerUp(glm::vec2 p,texture t) :pos(p),m_t(t) {};
	glm::vec2 pos;
	bool ifHit(const ball& b)const {
		const auto temp = pos - b.pos;

		return (temp.x*temp.x + temp.y*temp.y) < 110.25;
	};
	void draw(drawRenderer& d) const {
		d.draw({ pos.x - 8,pos.y - 8,16,16 }, fullPicUV, m_t.id, { 22,67,230,255 }, 1.0f);
	}
private:
	texture m_t;
};