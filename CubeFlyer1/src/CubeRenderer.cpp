#include "CubeRenderer.h"

#include <glm/gtc/matrix_transform.hpp> 

#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


//shader program initialization
static uint CompileShader(uint type, std::string source) {
	uint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

static std::string ReadFile(std::string path) {
	std::ifstream file(path);
	std::string line;
	std::stringstream ss;
	while (getline(file, line)) {
		ss << line << "\n";
	}
	return ss.str();
}

static uint InitProgram() {
	uint vertShader = CompileShader(GL_VERTEX_SHADER, ReadFile("res/shader.vert"));
	uint fragShader = CompileShader(GL_FRAGMENT_SHADER, ReadFile("res/shader.frag"));

	uint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(fragShader);
	glDeleteShader(vertShader);

	return program;
}



//method definitions
CubeRenderer::CubeRenderer()
{
	shaderProgram = InitProgram();

	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	uint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);

	uint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glUseProgram(shaderProgram);

	
}

void CubeRenderer::render(glm::vec3 pos, glm::mat4 rot)
{

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), pos);

	glm::mat4 proj = glm::perspective(
		1.0f,
		1.0f,
		0.1f,
		100.0f
	);

	proj =  proj * rot * trans ;

	int uniform = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniform, 1, GL_FALSE,&(proj[0][0]));

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	/*
	glBegin(GL_LINES);
	glVertex2d(0.5, 0.0);
	glVertex2d(-0.5, 0.0);
	glEnd();*/

}


