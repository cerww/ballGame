#include "gameMap.h"
#include "cw/things.h"
#include <algorithm>
#include <utility>
#include <random>


void gameMap::draw(drawRenderer& r) {
	for (const auto& i : m_balls) {
		i.draw(r);
	}
	for (const auto& i : m_blocks) {
		i.draw(r);
	}
}
void gameMap::addBall(double angle, glm::vec2 p) {

	m_balls.emplace_back(glm::vec2( p.x,0.0f ), m_ballText);
	m_balls.back().changeAngle(angle);
	//m_balls.back().
}

void gameMap::nextLayer(){

	std::random_device r;
	std::mt19937 m(r());
	std::bernoulli_distribution d(0.4);
	for (auto& i : m_blocks) {
		--i.m_pos.y;
	}
	
	for (int i = 0; i < 20; ++i) {
		if (d(m)) {
			m_blocks.emplace_back();
			m_blocks.back().m_current = 30;
			m_blocks.back().m_pos = {i,29};
		}
	}
	//std::cout << m_blocks.size() << std::endl;
}

bool gameMap::update() {
	/*
	for (auto& i : m_balls) {
		i.move();
	}

	return m_balls.size();
	*/
	for (int i = (int)m_balls.size()-1; i >=0 ;--i) {

		if (m_balls[i].pos.y < 0) {
			std::swap(m_balls.back(), m_balls[i]);
			m_balls.pop_back();
			continue;
		}
		else if (m_balls[i].pos.y>=900) {
			m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -m_balls[i].m_unitVec.y };
			m_balls[i].pos += 6.0f*m_balls[i].m_unitVec;
			continue;
		}
		if (m_balls[i].pos.x < 0 || m_balls[i].pos.x>800) {
			m_balls[i].m_unitVec = { -m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
			m_balls[i].pos += 6.0f*m_balls[i].m_unitVec;
			continue;
		}

		//auto oldPos = m_balls[i].pos;

		decltype(ifIntersectBox({}, {}, {})) c;
		std::get<0>(c) = 6.0f*m_balls[i].m_unitVec;

		for (unsigned j = 0; j < m_blocks.size(); ++j) {

				c = ifIntersectBox(m_balls[i].pos,6.0f*m_balls[i].m_unitVec,{40*m_blocks[j].m_pos.x,30*m_blocks[j].m_pos.y,40,30});
				switch (std::get<1>(c))	{
					case intersect::BOTTOM:
						m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -1.0*m_balls[i].m_unitVec.y };
						--m_blocks[j].m_current;
						std::cout << "bottom" << std::endl;
						j = m_blocks.size()+1;//break out of loop
						break;
					case intersect::TOP:
						m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -1.0*m_balls[i].m_unitVec.y };
						--m_blocks[j].m_current;
						std::cout << "top" << std::endl;
						j = m_blocks.size()+1;
						break;
					case intersect::LEFT:
						m_balls[i].m_unitVec = { -1.0*m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
						--m_blocks[j].m_current;
						std::cout << "left" << std::endl;
						j = m_blocks.size()+1;
						break;
					case intersect::RIGHT:
						m_balls[i].m_unitVec = { -1.0*m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
						--m_blocks[j].m_current;
						std::cout << "right" << std::endl;
						j = m_blocks.size()+1;
						break;
					case intersect::NONE:
						;
				}
			//}
		}
		m_balls[i].pos += std::get<0>(c);
	}
	return m_balls.size();
}