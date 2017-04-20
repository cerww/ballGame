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
	for (const auto& i : m_addBallPowerUps) {
		i.draw(r);
	}
}

void gameMap::clearBalls() {
	m_balls.clear();
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
	for (auto& i : m_addBallPowerUps) {
		i.pos.y -= 30;//move down 30px
	}
	
	for (int i = 0; i < 20; ++i) {
		if (d(m)) {
			m_blocks.emplace_back();
			m_blocks.back().m_current = 30;
			m_blocks.back().m_pos = {i,29};
		}
		else if(d(m)&&d(m)) {
			m_addBallPowerUps.emplace_back(glm::vec2{ i * 40 + 20,30 * 30 - 15 }, m_ballText);
		}
	}
	//std::cout << m_blocks.size() << std::endl;
}

std::tuple<bool,int> gameMap::update() {
	/*
	for (auto& i : m_balls) {
		i.move();
	}

	return m_balls.size();
	*/
	if (!m_balls.size()) {
		return { 0,0 };
	}

	unsigned newBallsToBeAdded = 0;

	for (int i = (int)m_balls.size()-1; i >=0 ;--i) {

		if (m_balls[i].pos.y < 0) {
			std::swap(m_balls.back(), m_balls[i]);
			m_balls.pop_back();
			continue;
		}
		else if (m_balls[i].pos.y>=900) {
			m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -m_balls[i].m_unitVec.y };
			m_balls[i].pos += 6.0f*m_balls[i].m_unitVec;
			if (m_balls[i].pos.y >= 900) {
				std::swap(m_balls.back(), m_balls[i]);
				m_balls.pop_back();
			}
			continue;
		}
		if (m_balls[i].pos.x < 0 || m_balls[i].pos.x>800) {
			m_balls[i].m_unitVec = { -m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
			m_balls[i].pos += 6.0f*m_balls[i].m_unitVec;
			continue;
		}

		for (unsigned j = 0; j < m_addBallPowerUps.size(); ++j) {
			if (m_addBallPowerUps[j].ifHit(m_balls[i])) {
				++newBallsToBeAdded;
				std::swap(m_addBallPowerUps[j], m_addBallPowerUps.back());
				m_addBallPowerUps.pop_back();
				break;//there will never be 2 power up ball thingys that will be hittable at once
			}
		}

		decltype(ifIntersectBox({}, {}, {})) c;
		std::get<0>(c) = 6.0f*m_balls[i].m_unitVec;

		for (unsigned j = 0; j < m_blocks.size(); ++j) {
			bool hitBox = true;
			c = ifIntersectBox(m_balls[i].pos,6.0f*m_balls[i].m_unitVec,{40*m_blocks[j].m_pos.x,30*m_blocks[j].m_pos.y,40,30});

			switch (std::get<1>(c))	{
				case intersect::BOTTOM:
					m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -1.0*m_balls[i].m_unitVec.y };
					std::cout << "bottom" << '\n';
					break;
				case intersect::TOP:
					m_balls[i].m_unitVec = { m_balls[i].m_unitVec.x, -1.0*m_balls[i].m_unitVec.y };
					std::cout << "top" << '\n';
					break;
				case intersect::LEFT:
					m_balls[i].m_unitVec = { -1.0*m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
					std::cout << "left" << '\n';
					break;
				case intersect::RIGHT:
					m_balls[i].m_unitVec = { -1.0*m_balls[i].m_unitVec.x, m_balls[i].m_unitVec.y };
					std::cout << "right" << '\n';
					break;
				case intersect::NONE:
					hitBox = false;
					break;
			}
			if (hitBox) {
				--m_blocks[j].m_current;
				if (!m_blocks[j].m_current) {
					std::swap(m_blocks[j], m_blocks.back());
					m_blocks.pop_back();
				}
				break;
			}
		}
		m_balls[i].pos += std::get<0>(c);
	}
	
	//return m_balls.size();
	if (!m_balls.size()) {
		return { 1,newBallsToBeAdded };
	}
	return { 0,newBallsToBeAdded };
}