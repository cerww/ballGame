#pragma once
#include <vector>
#include "block.h"
#include "ball.h"
class gameMap {
public:
	gameMap() = default;
	void update();
	void draw();
	void addBall();
private:
	void nextLayer();
	std::vector<ball> m_balls;
	std::vector<block> m_blocks;
	//unsigned m_cd = 10000;
};