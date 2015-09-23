#include "SpaceListener.h"
#include "Planet.h"
#include "PlanetAtributes.h"

#define PLANET_SCALING_RATIO 0.001f
#define PLAYER_START_POSITION_X 0
#define PLAYER_START_POSITION_Y 0
#define PLAYER_START_POSITION_Z -500
#define BASE_CAMERA_SPEED 50

SpaceListener::SpaceListener()
{
	// spheres
	Planet* sun = new Planet(SUN_SIZE * PLANET_SCALING_RATIO, SUN_MASS, SUN_TEXTURE, SUN_TEXTURE_HEIGHT, SUN_TEXTURE_WIDTH);
	this->modelsManager.push_front(sun);
	sun->setPosition(SUN_STARTING_X, SUN_STARTING_Y, SUN_STARTING_Z);

	Planet* earth = new Planet(EARTH_SIZE * PLANET_SCALING_RATIO, 10, EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
	this->modelsManager.push_front(earth);
	earth->setPosition(SUN_STARTING_X + EARTH_DISTANCE_FROM_SUN*PLANET_SCALING_RATIO, 0, 0);
	
	// set the player's starting position
	this->cameraManager.setCameraPosition(glm::vec3(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y, PLAYER_START_POSITION_Z));
}

SpaceListener::~SpaceListener()
{
	for (auto model : modelsManager)
	{
		delete model;
	}
	modelsManager.clear();
}

void SpaceListener::beginFrameCallback()
{

}

void SpaceListener::drawFrameCallback()
{
	modelsManager.draw(projectionMatrix, cameraManager.getViewMatrix());
}

void SpaceListener::endFrameCallback() {}

void SpaceListener::windowReshapeCallback(int width, int height, int previous_width, int previous_height)
{
	// aspect ratio
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projectionMatrix = glm::perspective(angle, ar, near1, far1);
}

bool SpaceListener::closeCallback()
{
	return true;
}

void SpaceListener::mouseMoveCallback(int x, int y, int centerX, int centerY)
{
	// get dX and dY
	int dx = x - centerX;
	int dy = y - centerY;

	if (dx != 0)
		dx = (dx > 0) ? 1 : -1;
	if (dy != 0)
		dy = (dy > 0) ? 1 : -1;

	this->cameraManager.look(dx, dy);

}

void SpaceListener::mouseDragCallback(int x, int y, int centerX, int centerY)
{
	std::cout << "mouse draged\n";
}

void SpaceListener::mouseClickCallback(int a, int b, int c, int d)
{
	std::cout << "mouse clicked\n";
}

void SpaceListener::keyboardPressCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key pressed: " << letter
		<< " a: " << a << " b: " << b << std::endl;
	switch (letter)
	{
	case 'w':
		cameraManager.moveForward(BASE_CAMERA_SPEED);
		break;
	case 's':
		cameraManager.moveBackward(BASE_CAMERA_SPEED);
		break;
	case 'a':
		cameraManager.panLeft(BASE_CAMERA_SPEED);
		break;
	case 'd':
		cameraManager.panRight(BASE_CAMERA_SPEED);
		break;
	case 't':
		cameraManager.panUp(BASE_CAMERA_SPEED);
		break;
	case 'g':
		cameraManager.panDown(BASE_CAMERA_SPEED);
		break;
	}
}

void SpaceListener::keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key released: " << letter
		<< " a: " << a << " b: " << b << std::endl;
}