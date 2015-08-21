#include "TSceneListener.h"
using namespace GraphicsEngine::EngineInterface;
using namespace Managers;

#define CAMERA_SPEED 0.2


TSceneListener::TSceneListener()
{
	TexturedCube* cube = new TexturedCube();
	this->modelsManager.push_front(cube);

	TexturedCube* cube2 = new TexturedCube();
	cube2->move(-0.1, 0, 0);
	this->modelsManager.push_front(cube2);

	TexturedCube* cube3 = new TexturedCube();
	cube3->move(0.1, 0, 0);
	this->modelsManager.push_front(cube3);
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

void TSceneListener::mouseMoveCallback()
{
	std::cout << "Mouse moved\n";
}

void TSceneListener::mouseDragCallback()
{
	std::cout << "mouse draged\n";
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