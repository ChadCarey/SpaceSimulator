#include "CameraManager.h"
using namespace glm;
using namespace Managers;

CameraManager* CameraManager::instance = NULL;

CameraManager::CameraManager() 
{
	this->setCameraPosition(glm::vec3(0.0,0.0,0.0));
	this->setCameraTarget(glm::vec3(0.0, 0.0, 10.0));
	this->setCameraUp(glm::vec3(0.0, 1.0, 0.0));
}

CameraManager* CameraManager::getInstance()
{
	if (instance == NULL)
	{
		std::cout << "Creating camera manager instance\n";
		instance = new CameraManager();
	}
	else
	{
		std::cout << "Returning pointer to existing camera\n";
	}
	return instance;
}

/**
* 
*/
glm::mat4 CameraManager::getViewMatrix()
{
	return this->LookAt(this->cameraPosition, this->cameraTarget, this->cameraUp);
}

glm::vec3 CameraManager::getCameraPosition()
{
	return this->cameraPosition;
}

glm::vec3 CameraManager::getCameraTarget()
{
	return this->cameraTarget;
}

glm::vec3 CameraManager::getCameraUp()
{
	return this->cameraUp;
}


// SETTERS
void CameraManager::setCameraPosition(const glm::vec3& newPosition)
{
	this->cameraPosition = newPosition;
}

void CameraManager::setCameraTarget(const glm::vec3& newTarget)
{
	this->cameraTarget = newTarget;
}

void CameraManager::setCameraUp(const glm::vec3& newUp)
{
	this->cameraUp = newUp;
}


// METHODS
void CameraManager::rotatate(int x, int y)
{
	std::cout << "rotate x: " << x << " rotate y: " << y << std::endl;
}

void CameraManager::rotatateX(int x)
{
	std::cout << "rotate x: " << x << std::endl;
}

void CameraManager::rotatateY(int y)
{
	std::cout << "rotate y: " << y << std::endl;
}

void CameraManager::panRight(int right)
{
	std::cout << "panRight: " << right << std::endl;
}

void CameraManager::panUp(int up)
{
	std::cout << "panUp: " << up << std::endl;
}

void CameraManager::moveForward(int forward)
{
	std::cout << "moveForward: " << forward << std::endl;
}

glm::mat4 CameraManager::LookAt(vec3& position, //camera position (eye)
	vec3& target,  //camera target
	vec3& up)
{
	return glm::lookAt(position, target, up);
}