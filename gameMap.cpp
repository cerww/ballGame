#include "gameMap.h"
#include "cw/things.h"
#include <algorithm>
#include <utility>

void gameMap::draw(drawRenderer& r) {
	
	for (const auto& i : m_balls) {
		i.draw(r);
	}
	for (const auto& i : m_blocks) {
		i.draw(r);
	}
}
void gameMap::addBall(float angle, glm::vec2 p) {
	m_balls.emplace_back(p,m_ballText);
}

void gameMap::update() {
	for (int i = (int)m_balls.size()-1; i >=0 ;--i) {
		m_balls[i].move();
		if (m_balls[i].pos.y < 0) {
			std::swap(m_balls.back(),m_balls[i]);
			m_balls.pop_back();
			continue;
		}
		for (int j = 0; j < m_blocks.size(); ++j) {
			if (boxInBox({ m_blocks[j].m_pos.x,m_blocks[j].m_pos.y,40,30 }, { m_balls[i].pos.x,m_balls[i].pos.y,15.0f,15.0f })) {
				
			}
		}

	}
}