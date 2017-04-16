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
				cdFrames = 10;
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
		if (!fireing) {
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
		}

	}

	glm::vec2 startingSpot;

	glm::vec2 towards;

	bool fireing = 0;

	int numBalls = 10;

	int ballsLeftToFire = 0;

	int cdFrames = 10;

	std::unique_ptr<gameMap> map;

	camera2D mainCam = camera2D(800, 900);
};

void ballGame::run() {
	//random stuff
	std::random_device r;
	std::mt19937 m(r());
	std::uniform_int_distribution<> d(0,800);

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
		if (!map->update()) {
			
			//map->ne
		}

		if (m_window.getMouseButton(mouseB::LEFT) == 1) {
			startFireing();
		}

		fire();

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