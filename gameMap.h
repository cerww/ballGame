#pragma once
#include <vector>
#include "block.h"
#include "ball.h"
#include "cw/imgLoader.h"

class gameMap {
public:
	gameMap() {
		m_ballText = imgLoader::loadPNG("circle.png");

		//m_blockText = imgLoader::loadPNG();
	};
	bool update();
	void draw(drawRenderer& r);
	void addBall(double angle,glm::vec2 p);
	void nextLayer();
private:

	std::vector<ball> m_balls;
	std::vector<block> m_blocks;

	texture m_ballText;
	texture m_blockText;

	//unsigned m_cd = 10000;
};