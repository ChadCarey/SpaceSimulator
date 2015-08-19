#include "TSceneListener.h"
using namespace GraphicsEngine::EngineInterface;
using namespace Managers;

TSceneListener::TSceneListener()
{
	glEnable(GL_DEPTH_TEST);
}

TSceneListener::~TSceneListener() {}

void TSceneListener::beginFrameCallback() {}

void TSceneListener::drawFrameCallback()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		modelsManager->draw(projectionMatrix, cameraManager->getViewMatrix());
}

void TSceneListener::endFrameCallback() {}

void TSceneListener::windowReshapeCallback(int width, int height, int previous_width, int previous_height)
{
	// aspect ratio
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projectionMatrix = glm::perspective(angle, ar, near1, far1);
}

void TSceneListener::startTimer(int miliseconds)
{

}

void TSceneListener::timerCallback(int value)
{

}

bool TSceneListener::closeCallback()
{
	return true;
}