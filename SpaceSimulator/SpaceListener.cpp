#include "SpaceListener.h"
#include "PlanetAtributes.h"

#define PLAYER_START_POSITION_X (5.0 / UNIVERSE_SCALE)
#define PLAYER_START_POSITION_Y 0
#define PLAYER_START_POSITION_Z (-4.0 / UNIVERSE_SCALE)
#define BASE_CAMERA_SPEED (3500.0 * UNIVERSE_SCALE)

#define PROJECTILE_SPEED 0.2f
#define PROJECTILE_MASS 0.7f
#define PROJECTILE_SIZE 4.0f
#define PROJECTILE_TEXTURE_FOLDER "energyTextures/"
#define PROJECTILE_TEXTURE_SIZE 256

#define MOUSE_PRIMARY 0
#define MOUSE_DOWN 0
#define MOUSE_UP 1

SpaceListener::SpaceListener()
{
    // skybox
    skybox = new Skybox();

	// Sun
    Planet* sun = new Planet(SUN_SIZE, SUN_MASS, SUN_TEXTURE_FOLDER, SUN_TEXTURE_SIZE);
	sun->setPosition(SUN_STARTING_X, SUN_STARTING_Y, SUN_STARTING_Z);
    
	// Mercury
	Planet* mercury = new Planet(MERCURY_SIZE, MERCURY_MASS, MERCURY_TEXTURE_FOLDER, MERCURY_TEXTURE_SIZE);
	sun->addNewOrbiter(mercury, MERCURY_DISTANCE_FROM_SUN);
   
	// Venus
	Planet* venus = new Planet(VENUS_SIZE, VENUS_MASS, VENUS_TEXTURE_FOLDER, VENUS_TEXTURE_SIZE);
	sun->addNewOrbiter(venus, VENUS_DISTANCE_FROM_SUN);

	// Earth
	Planet* earth = new Planet(EARTH_SIZE, EARTH_MASS, EARTH_TEXTURE_FOLDER, EARTH_TEXTURE_SIZE);
	sun->addNewOrbiter(earth, EARTH_DISTANCE_FROM_SUN);
    
    // Earth's moon
	Planet* moon = new Planet(MOON_SIZE, MOON_MASS, MOON_TEXTURE_FOLDER, MOON_TEXTURE_SIZE);
	earth->addNewOrbiter(moon, MOON_DISTANCE_FROM_EARTH);
    
	// mars
	Planet* mars = new Planet(MARS_SIZE, MARS_MASS, MARS_TEXTURE_FOLDER, MARS_TEXTURE_SIZE);
	sun->addNewOrbiter(mars, MARS_DISTANCE_FROM_SUN);
    this->addMoons(mars, MARS_MOONS);
    
	// Jupiter
	Planet* jupiter = new Planet(JUPITER_SIZE, JUPITER_MASS, JUPITER_TEXTURE_FOLDER, JUPITER_TEXTURE_SIZE);
	sun->addNewOrbiter(jupiter, JUPITER_DISTANCE_FROM_SUN);
    this->addMoons(jupiter, JUPITER_MOONS);
    this->addMoons(jupiter, JUPITER_MOONS);
    
	// Saturn
	Planet* saturn = new Planet(SATURN_SIZE, SATURN_MASS, SATURN_TEXTURE_FOLDER, SATURN_TEXTURE_SIZE);
	sun->addNewOrbiter(saturn, SATURN_DISTANCE_FROM_SUN);
    this->addMoons(saturn, SATURN_MOONS);

	// uranus
	Planet* uranus = new Planet(URANUS_SIZE, URANUS_MASS, URANUS_TEXTURE_FOLDER, URANUS_TEXTURE_SIZE);
	sun->addNewOrbiter(uranus, URANUS_DISTANCE_FROM_SUN);
    this->addMoons(uranus, URANUS_MOONS);

	// neptune
	Planet* neptune = new Planet(NEPTUNE_SIZE, NEPTUNE_MASS, NEPTUNE_TEXTURE_FOLDER, NEPTUNE_TEXTURE_SIZE);
	sun->addNewOrbiter(neptune, NEPTUNE_DISTANCE_FROM_SUN);
    this->addMoons(neptune, NEPTUNE_MOONS);

	// add the created system to the PlanetManager
	solarSystem.push_back(sun);

	// set the player's starting position
	this->cameraManager.setCameraPosition(glm::vec3(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y, PLAYER_START_POSITION_Z));

	// start the simulator paused
	paused = true;
}

SpaceListener::~SpaceListener()
{
    delete skybox;
	// will delete all of the solar system's planets and all of each planet's children as well
	for (auto p : solarSystem)
	{
		delete p;
	}
}

void SpaceListener::addMoons(Planet* p, int numMoons)
{
    double startingdistance = p->getSize()+ DEFAULT_MOON_DISTANCE;

    for (int i = 0; i < numMoons; ++i)
    {
        std::cout << "Adding moon " << i+1 << " of " << numMoons << std::endl;
        Planet* m = new Planet(DEFAULT_MOON_SIZE, DEFAULT_MOON_MASS, DEFAULT_MOON_TEXTURE_FOLDER, DEFAULT_MOON_TEXTURE_SIZE);
        p->addNewOrbiter(m, startingdistance);
        startingdistance += DEFAULT_MOON_DISTANCE;
    }
}

void SpaceListener::beginFrameCallback()
{
	if (!paused)
		solarSystem.update();
}

void SpaceListener::drawFrameCallback()
{
    // set the skybox possition and draw it
    glm::mat4 viewMat = cameraManager.getViewMatrix();
    skybox->setPosition(this->cameraManager.getCameraPosition());
    skybox->draw(projectionMatrix, viewMat);

    // draw the rest
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
    float scale = PROJECTILE_SIZE * 6;
    pos.x += dir.x * scale;
    pos.y += dir.y * scale;
    pos.z += dir.z * scale;
	Planet* projectile = new Planet(PROJECTILE_SIZE, PROJECTILE_MASS, PROJECTILE_TEXTURE_FOLDER, PROJECTILE_TEXTURE_SIZE);
	projectile->setPPosition(pos.x, pos.y, pos.z);
	projectile->setMovementVector(dir.x, dir.y, dir.z);
	this->solarSystem.push_back(projectile);
}