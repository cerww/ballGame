#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "cw/app.h"
#include "cw/drawableObj.h"
#include "cw/Rectangle.h"
#include "cw/things.h"
#include "gameMap.h"
#include <random>
#include <cmath>

class ballGame {
public:
	ballGame() {
		glfwMakeContextCurrent(m_window.getWindowPtr());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		if (glewInit() != GLEW_OK) {
			std::cout << "glew failed to init" << std::endl;
			glfwTerminate();
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		map = std::make_unique<gameMap>();
	};
	void run();
private:
	app m_window = app(glfwCreateWindow(800, 900, "ball", NULL, NULL));
	
	double angle = 0.0f;

	void fire() { 
		if (fireing&&ballsLeftToFire) {
			if (!cdFrames) {
				map->addBall(angle, startingSpot);
				cdFrames = 4;
				--ballsLeftToFire;
				if (!ballsLeftToFire) {
					fireing = 0;
				}
			}
			else {
				--cdFrames;
			}
		}
	};

	void startFireing() {
		if (!fireing&&!isRound) {
			cdFrames = 0;
			fireing = 1;
			ballsLeftToFire = numBalls;
			towards = mainCam.scrnToWorld(m_window.getMousePos());
			const auto temp = towards - startingSpot;
			//angle = ;
			//std::cout << temp.y << " " << temp.x << std::endl;
			angle = atan(temp.y/temp.x);
			//std::cout << angle << std::endl;
			if (angle < 0.0)
				angle += 3.1415926535;
			isRound = true;
		}

	}

	void endRound();

	glm::vec2 startingSpot;

	glm::vec2 towards;

	bool fireing = 0;

	int numBalls = 10;

	int ballsLeftToFire = 0;

	int cdFrames = 4;

	std::unique_ptr<gameMap> map;

	camera2D mainCam = camera2D(800, 900);

	unsigned ballsToAddNextRound = 0;

	bool isRound = 0;
};
void ballGame::endRound() {
	std::random_device r;
	std::mt19937 m(r());
	std::uniform_int_distribution<> d(0, 800);

	isRound = false;
	numBalls += ballsToAddNextRound;
	ballsToAddNextRound = 0;
	map->nextLayer();
	startingSpot = { d(m),0 };
}

void ballGame::run() {
	//random stuff
	
	std::random_device r;
	std::mt19937 m(r());
	std::uniform_int_distribution<> d(0, 800);

	Rectangle b({ 200.0f,200.0f,200.0f,200.0f }, { 200,200,200,200 });
	drawRenderer renderer;

	map->nextLayer();
	map->nextLayer();
	map->nextLayer();

	map->nextLayer();
	map->nextLayer();
	map->nextLayer();

	mainCam.setPos({ 400.0f, 450.0f });
	mainCam.update();


	startingSpot = { d(m),0 };
	glClearColor(1.0, 1.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(m_window.getWindowPtr())) {
		m_window.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		bool ended;
		int ballsToAdd;
		std::tie(ended, ballsToAdd) = map->update();
		ballsToAddNextRound += ballsToAdd;
		if (ended) {
			endRound();
		}

		if (m_window.getMouseButton(mouseB::LEFT) == 1) {
			startFireing();
		}

		if (m_window.getKey(Keys::ESC)==2) {
			map->clearBalls();
			endRound();
		}

		fire();

		renderer.draw({startingSpot.x-20,-20,40,40},fullPicUV, Rectangle::getFlatColor().id, { 150,22,160,200 }, 1.0f);

		map->draw(renderer);

		renderer.render(mainCam);

		m_window.wait();
	}

}

int main() {

	//std::cout << atan(1) << std::endl;
	if (!glfwInit())
		return -1;

	glewExperimental = GL_TRUE;

	ballGame g;
	g.run();

	glfwTerminate();

	return 0;
}