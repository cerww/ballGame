#pragma once
#include <vector>
#include "block.h"
#include "ball.h"
#include "cw/imgLoader.h"
#include <tuple>
#include "addBallPowerUp.h"

class gameMap {
public:
	gameMap() {
		m_ballText = imgLoader::loadPNG("circle.png");

		//m_blockText = imgLoader::loadPNG();
	};
	std::tuple<bool,int> update();//bool is for weather or not round just ended
	void draw(drawRenderer& r);
	void addBall(double angle,glm::vec2 p);
	void nextLayer();
	void clearBalls();//a safty thing!
private:

	std::vector<ball> m_balls;
	std::vector<block> m_blocks;
	std::vector<addBallPowerUp> m_addBallPowerUps;//best name ever!

	texture m_ballText;
	texture m_blockText;

	//unsigned m_cd = 10000;
};