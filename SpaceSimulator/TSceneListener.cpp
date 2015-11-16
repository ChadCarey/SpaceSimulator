#include "TSceneListener.h"
using namespace GraphicsEngine::EngineInterface;
using namespace Managers;

#define BASE_CAMERA_SPEED 0.7


TSceneListener::TSceneListener()
{
	// cubes
	TexturedCube* cube2 = new TexturedCube();
	this->modelsManager.push_front(cube2);
	cube2->setPosition(-10, 10, 0);

	TexturedCube* cube3 = new TexturedCube(1.5);
	this->modelsManager.push_front(cube3);
	cube3->setPosition(0, 10, 0);

	TexturedCube* cube4 = new TexturedCube(2);
	this->modelsManager.push_front(cube4);
	cube4->setPosition(10, 10, 0);

	// tetras
	TexturedTetra* tetra = new TexturedTetra();
	this->modelsManager.push_front(tetra);
	tetra->setPosition(-10, 0, 0);

	/*TexturedTetra* tetra2 = new TexturedTetra(1.5);
	this->modelsManager.push_front(tetra2);
	tetra2->setPosition(0, 0, 0);*/

	TexturedTetra* tetra3 = new TexturedTetra(2);
	this->modelsManager.push_front(tetra3);
	tetra3->setPosition(10, 0, 0);

	// spheres
/*	TexturedSphere* sphere = new TexturedSphere();
	this->modelsManager.push_front(sphere);
	sphere->setPosition(-10, -10, 0);

	TexturedSphere* sphere2 = new TexturedSphere(1.5);
	this->modelsManager.push_front(sphere2);
	sphere2->setPosition(0, -10, 0);
    */
	TexturedSphere* sphere3 = new TexturedSphere(2);
	this->modelsManager.push_front(sphere3);
	sphere3->setPosition(10, -10, 0);

	//warped = false;
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
		// get dX and dY
		int dx = x - centerX;
		int dy = y - centerY;
		
		if (dx != 0)
			dx = (dx > 0) ? 1 : -1;
		if (dy != 0)
			dy = (dy > 0) ? 1 : -1;

		this->cameraManager.look(dx, dy);

		// now warp the pointer back to the center of the screen
		//warped = true;
		glutWarpPointer(centerX, centerY);
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

void TSceneListener::keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b)
{
	std::cout << "key released: " << letter
		<< " a: " << a << " b: " << b << std::endl;
}