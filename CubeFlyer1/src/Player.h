#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Player {
public:
	double angleHor; //left-right
	double angleVer; //up-down
	double posX;
	double posY;
	double posZ;
private:
	int pressedForward;
	int pressedBack;
	int pressedRight;
	int pressedLeft;
	int pressedUp;
	int pressedDown;
	double turnHor;
	double turnVer;

public:
	Player();
	
	void handleMouse(double offsetX, double offsetY);
	void handleKey(int key, int action);
	void step();
	void printPos();
	void printPressed();
	glm::vec3 getPos();
	glm::mat4 getRot();

private:
	double roundDouble(double x);

};

