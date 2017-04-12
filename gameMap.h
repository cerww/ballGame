#pragma once
#include <vector>
#include "block.h"
#include "ball.h"
class gameMap {
public:
	gameMap() = default;
	void update();
private:
	std::vector<ball> m_balls;
	std::vector<block> m_blocks;
};