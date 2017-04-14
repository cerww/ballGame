#pragma once
#include <vector>
#include "block.h"
#include "ball.h"
class gameMap {
public:
	gameMap() = default;
	void update();
	void draw(drawRenderer& r);
	void addBall(float angle,glm::vec2 p);
private:
	void nextLayer();
	std::vector<ball> m_balls;
	std::vector<block> m_blocks;

	texture m_ballText;
	texture m_blockText;

	//unsigned m_cd = 10000;
};