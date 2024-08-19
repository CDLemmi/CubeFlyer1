#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

typedef unsigned int uint;

class CubeRenderer {
private:
	uint shaderProgram;
	uint vertexBuffer;
	uint vertexArray;

	float vertices[24] = {
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f
	};

	/*float vertices[24] = {
		-0.6f,  -0.6f,  0.5f,
		-0.4f,  -0.4f, -0.5f,
		-0.3f, -0.2f,  0.5f,
		-0.1f,  0.0f, -0.5f,
		 0.0f,  0.2f,  0.5f,
		 0.2f,  0.4f, -0.5f,
		 0.3f,  0.6f,  0.5f,
		 0.5f,  0.8f, -0.5f
	};*/

	uint indices[24] = {
		0, 1,
		1, 3,
		3, 2,
		2, 0,
		4, 5,
		5, 7,
		7, 6,
		6, 4,
		0, 4,
		1, 5,
		2, 6,
		3, 7
	};

public:
	CubeRenderer();

	void render(glm::vec3 pos, glm::mat4 rot);

};

