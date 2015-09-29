#include "SpaceListener.h"
#include "PlanetAtributes.h"

#define PLAYER_START_POSITION_X (5.0 / UNIVERSE_SCALE)
#define PLAYER_START_POSITION_Y 0
#define PLAYER_START_POSITION_Z (-4.0 / UNIVERSE_SCALE)
#define BASE_CAMERA_SPEED (3500.0 * UNIVERSE_SCALE)

SpaceListener::SpaceListener()
{
	// Sun
	sun = new Planet(SUN_SIZE, SUN_MASS, 
		SUN_TEXTURE, SUN_TEXTURE_HEIGHT, SUN_TEXTURE_WIDTH);
	sun->setPosition(SUN_STARTING_X, SUN_STARTING_Y, SUN_STARTING_Z);

	// Earth
	Planet* earth = new Planet(EARTH_SIZE, EARTH_MASS, 
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
	sun->addNewOrbiter(earth, EARTH_DISTANCE_FROM_SUN);
	
	// Earth's moon
	Planet* moon = new Planet(EARTH_MOON_SIZE, EARTH_MOON_MASS,
		EARTH_MOON_TEXTURE, EARTH_MOON_TEXTURE_HEIGHT, EARTH_MOON_TEXTURE_WIDTH);
	earth->addNewOrbiter(moon, EARTH_MOON_DISTANCE_FROM_EARTH);
	
	// set the player's starting position
	this->cameraManager.setCameraPosition(glm::vec3(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y, PLAYER_START_POSITION_Z));

	// start the simulator paused
	paused = true;
}

SpaceListener::~SpaceListener()
{
	// sun will delete all of it's children as well
	delete sun;
}

void SpaceListener::beginFrameCallback()
{
	if (!paused)
		sun->update();
}

void SpaceListener::drawFrameCallback()
{
	sun->draw(projectionMatrix, cameraManager.getViewMatrix());
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
	case 'p':
		if (paused)
			paused = false;
		else
			paused = true;
		break;
	}
}

void SpaceListener::keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key released: " << letter
		<< " a: " << a << " b: " << b << std::endl;
}