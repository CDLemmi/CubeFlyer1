#include "Player.h"

#include <iostream>
#include <cmath>

#define PI 3.1415926535897932384626433

const int KEY_FORWARD = GLFW_KEY_W;
const int KEY_BACK = GLFW_KEY_S;
const int KEY_LEFT = GLFW_KEY_A;
const int KEY_RIGHT = GLFW_KEY_D;
const int KEY_UP = GLFW_KEY_SPACE;
const int KEY_DOWN = GLFW_KEY_LEFT_SHIFT;

const double MOVE_SPEED = 3.0;
const double MOUSE_SENSI = 0.002;

Player::Player()
	: angleHor(0), angleVer(0.5*PI), posX(0), posY(-5), posZ(0)
{
}

void Player::step(double dt) {
	if (pressedForward) {
		posX += sin(angleHor) * MOVE_SPEED * dt;
		posY += cos(angleHor) * MOVE_SPEED * dt;
	}

	if (pressedRight) {
		posX += -cos(angleHor) * MOVE_SPEED * dt;
		posY += sin(angleHor) * MOVE_SPEED * dt;
	}

	if (pressedLeft) {
		posX += cos(angleHor) * MOVE_SPEED * dt;
		posY += -sin(angleHor) * MOVE_SPEED * dt;
	}

	if (pressedBack) {
		posX += -sin(angleHor) * MOVE_SPEED * dt;
		posY += -cos(angleHor) * MOVE_SPEED * dt;
	}

	if (pressedUp) {
		posZ += MOVE_SPEED * dt;
	}
	
	if (pressedDown) {
		posZ -= MOVE_SPEED * dt;
	}

	angleHor -= turnHor * MOUSE_SENSI;
	angleVer -= turnVer * MOUSE_SENSI;

	if (angleVer > PI) {
		angleVer = PI;
	}
	if (angleVer < 0) {
		angleVer = 0;
	}
	if (angleHor > PI) {
		angleHor -= 2*PI;
	}
	if (angleHor < -PI) {
		angleHor += PI;
	}
	turnHor = 0.0;
	turnVer = 0.0;
}

glm::vec3 Player::getPos() {
	return glm::vec3((float)posX, (float)posY, (float)posZ);
}

glm::mat4 Player::getRot() {
	auto x = glm::rotate(glm::mat4(1.0f), (float) angleVer, glm::vec3(1.0f, 0.0f, 0.0)); //angleVer applied
	return glm::rotate(x, (float)angleHor, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Player::handleKey(int key, int action) {
	switch (key) {
	case KEY_FORWARD:
		pressedForward = action != GLFW_RELEASE;
		break;
	case KEY_BACK:
		pressedBack = action != GLFW_RELEASE;
		break;
	case KEY_LEFT:
		pressedLeft = action != GLFW_RELEASE;
		break;
	case KEY_RIGHT:
		pressedRight = action != GLFW_RELEASE;
		break;
	case KEY_UP:
		pressedUp = action != GLFW_RELEASE;
		break;
	case KEY_DOWN:
		pressedDown = action != GLFW_RELEASE;
		break;
	}
}

void Player::handleMouse(double offsetX, double offsetY) {
	turnHor += offsetX;
	turnVer += offsetY;
}


void Player::printPressed() {
	std::cout << "currently pressed: "
		<< "forward=" << pressedForward
		<< ";back=" << pressedBack
		<< ";left=" << pressedLeft
		<< ";right=" << pressedRight
		<< ";up=" << pressedUp
		<< ";down=" << pressedDown
		<< std::endl;
}


void Player::printPos() {
	std::cout << "current player position:"
		<< " x=" << roundDouble(posX)
		<< ";y=" << roundDouble(posY)
		<< ";z=" << roundDouble(posZ)
		<< ";angleHor=" << roundDouble(angleHor)
		<< ";angleVer=" << roundDouble(angleVer)
		<< std::endl;
		
		
}

double Player::roundDouble(double x) {
	double value = (int)(x * 100 + .5);
	return (double)value / 100;
}

