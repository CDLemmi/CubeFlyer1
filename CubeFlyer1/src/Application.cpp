#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>

#include "FpsCounter.h"
#include "Player.h"
#include "CubeRenderer.h"


double mouseX;
double mouseY;
Player player;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	player.handleKey(key, action);
}

void pressedCursorPosCallback(GLFWwindow* window, double x, double y) {
	player.handleMouse(x - mouseX, -(y - mouseY));
	mouseX = x;
	mouseY = y;
}
void notPressedCursorPosCallback(GLFWwindow* window, double x, double y) {
	mouseX = x;
	mouseY = y;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, pressedCursorPosCallback);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, notPressedCursorPosCallback);
		}
	}
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



int main() {

	std::cout << "Hello World!" << std::endl;

	if (!glfwInit()) {
		std::cout << "Error: Failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Cube Flyer 1", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSwapInterval(0);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(0);


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "ALARM" << std::endl;
		return -1;
	}

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	FpsCounter fpsCounter;
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	CubeRenderer cubeRenderer;


	glfwSetCursorPosCallback(window, notPressedCursorPosCallback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		double dt = fpsCounter.incCounter();

		//player.printPos();
		player.step(dt);
		auto pos = player.getPos();
		auto rot = player.getRot();

		cubeRenderer.render(pos, rot);

		glfwSwapBuffers(window);


		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL Error] (" << std::hex << error << "): " << std::endl;
		}

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}