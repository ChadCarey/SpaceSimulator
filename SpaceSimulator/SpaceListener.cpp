#include "SpaceListener.h"
#include "PlanetAtributes.h"

#define PLAYER_START_POSITION_X (5.0 / UNIVERSE_SCALE)
#define PLAYER_START_POSITION_Y 0
#define PLAYER_START_POSITION_Z (-4.0 / UNIVERSE_SCALE)
#define BASE_CAMERA_SPEED (3500.0 * UNIVERSE_SCALE)

#define PROJECTILE_SPEED 0.2f
#define PROJECTILE_MASS 0.7f
#define PROJECTILE_SIZE 4.0f
#define PROJECTILE_TEXTURE "energy.bmp"
#define PROJECTILE_TEXTURE_HEIGHT 200
#define PROJECTILE_TEXTURE_WIDTH 300

#define MOUSE_PRIMARY 0
#define MOUSE_DOWN 0
#define MOUSE_UP 1

SpaceListener::SpaceListener()
{
	// Sun
	Planet* sun = new Planet(SUN_SIZE, SUN_MASS, 
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//SUN_TEXTURE, SUN_TEXTURE_HEIGHT, SUN_TEXTURE_WIDTH);
	sun->setPosition(SUN_STARTING_X, SUN_STARTING_Y, SUN_STARTING_Z);

	// Mercury
	Planet* mercury = new Planet(MERCURY_SIZE, MERCURY_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//MERCURY_TEXTURE, MERCURY_TEXTURE_HEIGHT, MERCURY_TEXTURE_WIDTH);
	sun->addNewOrbiter(mercury, MERCURY_DISTANCE_FROM_SUN);

	// Venus
	Planet* venus = new Planet(VENUS_SIZE, VENUS_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//VENUS_TEXTURE, VENUS_TEXTURE_HEIGHT, VENUS_TEXTURE_WIDTH);
	sun->addNewOrbiter(venus, VENUS_DISTANCE_FROM_SUN);

	// Earth
	Planet* earth = new Planet(EARTH_SIZE, EARTH_MASS, 
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
	sun->addNewOrbiter(earth, EARTH_DISTANCE_FROM_SUN);
	// Earth's moon
	Planet* moon = new Planet(MOON_SIZE, MOON_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//MOON_TEXTURE, MOON_TEXTURE_HEIGHT, MOON_TEXTURE_WIDTH);
	earth->addNewOrbiter(moon, MOON_DISTANCE_FROM_EARTH);
	
	// mars
	Planet* mars = new Planet(MARS_SIZE, MARS_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//MARS_TEXTURE, MARS_TEXTURE_HEIGHT, MARS_TEXTURE_WIDTH);
	sun->addNewOrbiter(mars, MARS_DISTANCE_FROM_SUN);

	// Jupiter
	Planet* jupiter = new Planet(JUPITER_SIZE, JUPITER_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//JUPITER_TEXTURE, JUPITER_TEXTURE_HEIGHT, JUPITER_TEXTURE_WIDTH);
	sun->addNewOrbiter(jupiter, JUPITER_DISTANCE_FROM_SUN);

	// Saturn
	Planet* saturn = new Planet(SATURN_SIZE, SATURN_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//SATURN_TEXTURE, SATURN_TEXTURE_HEIGHT, SATURN_TEXTURE_WIDTH);
	sun->addNewOrbiter(saturn, SATURN_DISTANCE_FROM_SUN);

	// uranus
	Planet* uranus = new Planet(URANUS_SIZE, URANUS_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//URANUS_TEXTURE, URANUS_TEXTURE_HEIGHT, URANUS_TEXTURE_WIDTH);
	sun->addNewOrbiter(uranus, URANUS_DISTANCE_FROM_SUN);

	// neptune
	Planet* neptune = new Planet(NEPTUNE_SIZE, NEPTUNE_MASS,
		EARTH_TEXTURE, EARTH_TEXTURE_HEIGHT, EARTH_TEXTURE_WIDTH);
		//NEPTUNE_TEXTURE, NEPTUNE_TEXTURE_HEIGHT, NEPTUNE_TEXTURE_WIDTH);
	sun->addNewOrbiter(neptune, NEPTUNE_DISTANCE_FROM_SUN);

	// add the created system to the PlanetManager
	solarSystem.push_back(sun);

	// set the player's starting position
	this->cameraManager.setCameraPosition(glm::vec3(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y, PLAYER_START_POSITION_Z));

	// start the simulator paused
	paused = true;
}

SpaceListener::~SpaceListener()
{
	// will delete all of the solar system's planets and all of each planet's children as well
	for (auto p : solarSystem)
	{
		delete p;
	}
}

void SpaceListener::beginFrameCallback()
{
	if (!paused)
		solarSystem.update();
}

void SpaceListener::drawFrameCallback()
{
	solarSystem.draw(projectionMatrix, cameraManager.getViewMatrix());
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
	std::cout << "mouse clicked a: " << a << " b: " << b << " c: " << c << " d: " << d << std::endl;
	switch (a)
	{
	case MOUSE_UP:
		std::cout << "mouse up\n";
		while (true);
		break;
	case MOUSE_PRIMARY:
		if (b == MOUSE_DOWN)
		{
			std::cout << "fire\n";
			fire();
		}
		else
		{

		}
		break;
	}
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

void SpaceListener::fire()
{
	glm::vec3 pos = cameraManager.getCameraPosition();
	glm::vec3 dir = cameraManager.getForwardVector() * PROJECTILE_SPEED;
	// move it forwad so it doesn't spawn on top of us
	pos.x += dir.x * 15.0;
	pos.y += dir.y * 15.0;
	pos.z += dir.z * 15.0;
	Planet* projectile = new Planet(PROJECTILE_SIZE, PROJECTILE_MASS,
		PROJECTILE_TEXTURE, PROJECTILE_TEXTURE_HEIGHT, PROJECTILE_TEXTURE_WIDTH);
	projectile->setPPosition(pos.x, pos.y, pos.z);
	projectile->setMovementVector(dir.x, dir.y, dir.z);
	this->solarSystem.push_back(projectile);
}