#include "CameraManager.h"
using namespace glm;
using namespace Managers;

#define ROTATION_SPEED 0.02f

/**
*
*/
CameraManager::CameraManager() 
{
	this->setCameraPosition(glm::vec3(0, 0, -15));
	this->setCameraUp(glm::vec3(0.0, 1.0, 0.0));

	this->setUpVector(glm::vec3(0.0, 1.0, 0.0));
	this->setForwardVector(glm::vec3(0.0, 0.0, 1.0));
}

/**
*
*/
CameraManager::CameraManager(const CameraManager& cam)
{
	this->setCameraPosition(cam.getCameraPosition());
	this->setCameraUp(cam.getCameraUp());

	this->setUpVector(cam.getUpVector());
	this->setForwardVector(cam.getForwardVector());
}

/**
*
*/
glm::vec3 CameraManager::getRightVector() const
{
	return cross(this->cameraUp, this->forwardVector);
}

/**
*
*/
glm::vec3 CameraManager::getForwardVector() const
{
	return this->forwardVector;
}

/**
*
*/
glm::vec3 CameraManager::getUpVector() const
{
	return this->upVector;
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
	glm::vec3 target;
	target.x = this->cameraPosition.x + this->forwardVector.x;
	target.y = this->cameraPosition.y + this->forwardVector.y;
	target.z = this->cameraPosition.z + this->forwardVector.z;
	return target;
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
glm::mat4 CameraManager::getViewMatrix() const
{
	return glm::lookAt(this->getCameraPosition(), this->getCameraTarget(), this->getCameraUp());
}

/**
*
*/
void CameraManager::setCameraPosition(const glm::vec3& newPosition)
{
	this->cameraPosition.x = newPosition.x;
	this->cameraPosition.y = newPosition.y;
	this->cameraPosition.z = newPosition.z;
}

/**
*
*/
void CameraManager::setCameraUp(const glm::vec3& newUp)
{
	this->cameraUp.x = newUp.x;
	this->cameraUp.y = newUp.y;
	this->cameraUp.z = newUp.z;
}

/**
*
*/
void CameraManager::setUpVector(const glm::vec3& newUp)
{
	glm::vec3 norm = normalize(newUp);
	this->upVector.x = norm.x;
	this->upVector.y = norm.y;
	this->upVector.y = norm.y;
}

/**
*
*/
void CameraManager::setForwardVector(const glm::vec3& newForward)
{
	glm::vec3 norm = normalize(newForward);
	this->forwardVector.x = norm.x;
	this->forwardVector.y = norm.y;
	this->forwardVector.z = norm.z;
}

/**
*
*/
void CameraManager::lookRight(float right)
{
	glm::vec3 rVector = this->getRightVector();
	glm::vec3 fVector = this->getForwardVector();
	glm::vec3 newFVector = fVector - ((rVector* right) * ROTATION_SPEED);

	this->setForwardVector(newFVector);
	this->correctUp();
}

/**
*
*/
void CameraManager::lookUp(float up)
{
	glm::vec3 uVector = this->getUpVector();
	glm::vec3 fVector = this->getForwardVector();
	glm::vec3 newUVector = uVector + ((fVector * up) * ROTATION_SPEED);
	glm::vec3 newFVector = fVector - ((uVector* up) * ROTATION_SPEED);

	this->setUpVector(newUVector);
	this->setForwardVector(newFVector);
	//this->correctRight();
}

/**
*
*/
void CameraManager::panRight(float right)
{
	glm::vec3 rVec = this->getRightVector() * right;
	std::cout << "panRight: x:" << rVec.x << " y:" << rVec.y << " z:" << rVec.z << std::endl;
	this->cameraPosition.x -= rVec.x;
	this->cameraPosition.y -= rVec.y;
	this->cameraPosition.z -= rVec.z;
}

void CameraManager::panUp(float up)
{
	glm::vec3 rVec = this->getUpVector() * up;
	std::cout << "panUp: x:" << rVec.x << " y:" << rVec.y << " z:" << rVec.z << std::endl;
	this->cameraPosition.x += rVec.x;
	this->cameraPosition.y += rVec.y;
	this->cameraPosition.z += rVec.z;
}

/**
*
*/
void CameraManager::moveForward(float forward)
{
	std::cout << "moveForward: " << forward << std::endl;
	glm::vec3 direction = this->getForwardVector()*forward;
	this->cameraPosition.x += direction.x;
	this->cameraPosition.y += direction.y;
	this->cameraPosition.z += direction.z;
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
	this->lookRight(dx);
	this->lookUp(dy);
}

/**
*
*/
void CameraManager::correctUp()
{
	glm::vec3 correction = cross(this->getForwardVector(), this->getRightVector());
	this->setUpVector(correction);
}
