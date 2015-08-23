#include "TSceneListener.h"
using namespace GraphicsEngine::EngineInterface;
using namespace Managers;

#define CAMERA_SPEED 0.2


TSceneListener::TSceneListener()
{
	TexturedSphere* sphere = new TexturedSphere();
	this->modelsManager.push_front(sphere);

	TexturedSphere* sphere2 = new TexturedSphere(2);
	this->modelsManager.push_front(sphere2);
	sphere2->setPosition(-10, 0, 0);

	TexturedTetra* tetra = new TexturedTetra();
	this->modelsManager.push_front(tetra);
	tetra->move(-15, 10, -5);

	TexturedCube* cube2 = new TexturedCube(2);
	this->modelsManager.push_front(cube2);
	cube2->move(-7, -5, -3);
	cube2->setRotation(10, 35, 45);

	TexturedCube* cube3 = new TexturedCube(1.5);
	this->modelsManager.push_front(cube3);
	cube3->move(7, 5, 3);
	cube3->setRotation(35, 45, 10);

	TexturedCube* cube4 = new TexturedCube(0.5);
	cube4->move(-3, -7, -5);
	this->modelsManager.push_front(cube4);
	cube4->rotate(45, 35, 10);

	TexturedCube* cube5 = new TexturedCube(0.75);
	cube5->move(3, 7, -5);
	this->modelsManager.push_front(cube5);
	cube5->rotate(45, 10, 35);

	TexturedCube* cube6 = new TexturedCube(1.25);
	cube6->move(-5, -3, -7);
	this->modelsManager.push_front(cube6);
	cube6->rotate(-10, -35, -45);

	TexturedCube* cube7 = new TexturedCube(1.75);
	cube7->move(5, 3, 7);
	this->modelsManager.push_front(cube7);
	cube7->rotate(-35, -45, -1);

	warped = false;
}

TSceneListener::~TSceneListener() 
{
	for (auto model : modelsManager)
	{
		delete model;
	}
	modelsManager.clear();
}

void TSceneListener::beginFrameCallback()
{
	
}

void TSceneListener::drawFrameCallback()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		modelsManager.draw(projectionMatrix, cameraManager.getViewMatrix());
}

void TSceneListener::endFrameCallback() {}

void TSceneListener::windowReshapeCallback(int width, int height, int previous_width, int previous_height)
{
	// aspect ratio
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projectionMatrix = glm::perspective(angle, ar, near1, far1);
}

bool TSceneListener::closeCallback()
{
	return true;
}

void TSceneListener::mouseMoveCallback(int x, int y, int centerX, int centerY)
{
	if (!warped)
	{
		// get dX and dY
		int dx = x - centerX;
		int dy = y - centerY;
		std::cout << "Mouse moved, x: " << x << " y: " << y << std::endl;
		std::cout << "dx: " << dx << " dy: " << dy << std::endl;
		
		cameraManager.look(dx, dy);

		// now warp the pointer back to the center of the screen
		//warped = true;
		//glutWarpPointer(centerX, centerY);
	}
	else
	{
		// now that the pointer has warped we need to clear the flag for the next movement
		// this prevents a recursive call on glutWarpPointer()
		warped = false;
	}
}

void TSceneListener::mouseDragCallback(int x, int y, int centerX, int centerY)
{
	std::cout << "mouse draged\n";
}

void TSceneListener::mouseClickCallback(int a, int b, int c, int d)
{
	std::cout << "mouse clicked\n";
}

void TSceneListener::keyboardPressCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key pressed: " << letter 
		<< " a: " << a << " b: " << b << std::endl;
	switch (letter)
	{
	case 'w':
		cameraManager.moveForward(CAMERA_SPEED);
		break;
	case 'a':
		cameraManager.panLeft(CAMERA_SPEED);
		break;
	case 'd':
		cameraManager.panRight(CAMERA_SPEED);
		break;
	case 's':
		cameraManager.moveBackward(CAMERA_SPEED);
		break;
	}
}

void TSceneListener::keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key released: " << letter
		<< " a: " << a << " b: " << b << std::endl;
}