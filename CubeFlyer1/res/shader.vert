#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 proj;
uniform mat4 trans;
uniform mat4 rot;

void main() {
	gl_Position = proj * rot * trans * vec4(aPos, 1.0);
}