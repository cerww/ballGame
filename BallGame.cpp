#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "cw/app.h"
#include "cw/drawableObj.h"
#include "cw/Rectangle.h"
#include "cw/things.h"

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
	};
	void run();
private:
	app m_window = app(glfwCreateWindow(800, 800, "ball", NULL, NULL));
	
	math::radians angle = 0.0f;

	void fire() { 
		cdFrames = 10;
		--ballsLeftToFire;
		if (!ballsLeftToFire) {
			fireing = 0;
		}
	};

	bool fireing = 0;

	int numBalls = 1;

	int ballsLeftToFire = 0;

	int cdFrames = 10;
};

void ballGame::run() {
	//glewInit();
	Rectangle b({ 200.0f,200.0f,200.0f,200.0f }, { 200,200,200,200 });
	drawRenderer renderer;

	camera2D mainCam(800,800);
	mainCam.setPos({ 400.0f, 400.0f });
	mainCam.update();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(m_window.getWindowPtr())) {
		m_window.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_window.wait();
	}

}

int main() {
	
	if (!glfwInit())
		return -1;

	glewExperimental = GL_TRUE;

	ballGame g;
	g.run();

	glfwTerminate();

	return 0;
}