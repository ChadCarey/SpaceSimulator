#include "CameraManager.h"
using namespace glm;
using namespace Managers;

CameraManager* CameraManager::instance = NULL;

/**
*
*/
CameraManager::CameraManager() 
{
	this->setCameraPosition(glm::vec3(1, 4, 15.4));
	this->setCameraTarget(glm::vec3(0.0, 0.0, 0.0));
	this->setCameraUp(glm::vec3(0.0, 1.0, 0.0));
}

/**
*
*/
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

/**
*
*/
glm::vec3 CameraManager::getCameraPosition()
{
	return this->cameraPosition;
}

/**
*
*/
glm::vec3 CameraManager::getCameraTarget()
{
	return this->cameraTarget;
}

/**
*
*/
glm::vec3 CameraManager::getCameraUp()
{
	return this->cameraUp;
}

/**
*
*/
void CameraManager::setCameraPosition(const glm::vec3& newPosition)
{
	this->cameraPosition = newPosition;
}

/**
*
*/
void CameraManager::setCameraTarget(const glm::vec3& newTarget)
{
	this->cameraTarget = newTarget;
}

/**
*
*/
void CameraManager::setCameraUp(const glm::vec3& newUp)
{
	this->cameraUp = newUp;
}


/**
*
*/
void CameraManager::rotateLeft(int left)
{
	std::cout << "rotate left: " << left << std::endl;
}

/**
*
*/
void CameraManager::rotateRight(int right)
{
	rotateLeft(-right);
}

/**
*
*/
void CameraManager::lookUp(int value)
{
	std::cout << "loop up: " << value << std::endl;
}

/**
*
*/
void CameraManager::lookDown(int value)

{
	lookUp(-value);
}

/**
*
*/
void CameraManager::lookLeft(int value)

{
	std::cout << "loop left: " << value << std::endl;
}

/**
*
*/
void CameraManager::lookRight(int value)

{
	lookLeft(-value);
}

/**
*
*/
void CameraManager::panRight(int right)
{
	std::cout << "panRight: " << right << std::endl;
}

/**
*
*/
void CameraManager::panLeft(int left)
{
	panRight(-left);
}

/**
*
*/
void CameraManager::panUp(int up)
{
	std::cout << "panUp: " << up << std::endl;
}

/**
*
*/
void CameraManager::panDown(int down)
{
	panUp(-down);
}

/**
*
*/
void CameraManager::moveForward(int forward)
{
	std::cout << "moveForward: " << forward << std::endl;
}

/**
*
*/
void CameraManager::moveBackward(int backward)
{
	moveForward(-backward);
}

/**
*
*/
glm::mat4 CameraManager::LookAt(vec3& position, //camera position (eye)
	vec3& target,  //camera target
	vec3& up)
{
	return glm::lookAt(position, target, up);
}