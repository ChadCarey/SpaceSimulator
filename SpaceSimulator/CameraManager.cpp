#include "CameraManager.h"
using namespace glm;
using namespace Managers;

/**
*
*/
CameraManager::CameraManager() 
{
	this->setCameraPosition(glm::vec3(0, 0, -15));
	this->setCameraTarget(glm::vec3(0.0, 0.0, 0.0));
	this->setCameraUp(glm::vec3(0.0, 1.0, 0.0));
}

/**
*
*/
CameraManager::CameraManager(const CameraManager& cam)
{
	this->setCameraPosition(cam.getCameraPosition());
	this->setCameraTarget(cam.getCameraTarget());
	this->setCameraUp(cam.getCameraUp());
}


/**
* 
*/
glm::mat4 CameraManager::getViewMatrix() const
{
	return glm::lookAt(this->cameraPosition, this->cameraTarget, this->cameraUp);
}

/**
*
*/
glm::vec3 CameraManager::getCameraPosition() const
{
	return this->cameraPosition;
}

/**
*
*/
glm::vec3 CameraManager::getCameraTarget() const
{
	return this->cameraTarget;
}

/**
*
*/
glm::vec3 CameraManager::getCameraUp() const
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
void CameraManager::rotateLeft(float left)
{
	std::cout << "rotate left: " << left << std::endl;
}

/**
*
*/
void CameraManager::rotateRight(float right)
{
	rotateLeft(-right);
}

/**
*
*/
void CameraManager::lookUp(float value)
{
	std::cout << "loop up: " << value << std::endl;
}

/**
*
*/
void CameraManager::lookDown(float value)

{
	lookUp(-value);
}

/**
*
*/
void CameraManager::lookLeft(float value)

{
	std::cout << "loop left: " << value << std::endl;
}

/**
*
*/
void CameraManager::lookRight(float value)

{
	lookLeft(-value);
}

/**
*
*/
void CameraManager::panRight(float right)
{
	std::cout << "panRight: " << right << std::endl;
	this->cameraPosition.x -= right;
	this->cameraTarget.x -= right;
}

/**
*
*/
void CameraManager::panUp(float up)
{
	std::cout << "panUp: " << up << std::endl;
}

/**
*
*/
void CameraManager::panDown(float down)
{
	panUp(-down);
}

/**
*
*/
void CameraManager::moveForward(float forward)
{
	std::cout << "moveForward: " << forward << std::endl;
	cameraPosition.z += forward;
	cameraTarget.z += forward;
}

/**
*
*/
glm::mat4 CameraManager::LookAt(vec3& position, //camera position (eye)
	vec3& target,  //camera target
	vec3& up) const
{
	return glm::lookAt(position, target, up);
}

/**
*
*/
void CameraManager::look(int dx, int dy)
{
	angleX += dx;
	angleX = angleX % 360;
	if (angleX < 0)
		angleX += 360;
	
	angleY += dy;
	angleY = angleY % 360;
	if (angleY < 0)
		angleY += 360;
}