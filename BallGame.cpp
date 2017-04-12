#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "cw/app.h"
#include "cw/drawableObj.h"

class ballGame {
public:
	ballGame() {
	
	};
	void run();
private:
	app m_window = app(glfwCreateWindow(800,800,"ball",NULL,NULL));;

};

void ballGame::run() {

	drawRenderer renderer;

	camera2D mainCam(800,800);
	mainCam.setPos({ 400.0f, 400.0f });
	mainCam.update();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(m_window.getWindowPtr())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_window.wait();
	}

}

int main() {
	
	if (!glfwInit())
		return -1;

	glewExperimental = GL_TRUE;



	glfwTerminate();

	return 0;
}