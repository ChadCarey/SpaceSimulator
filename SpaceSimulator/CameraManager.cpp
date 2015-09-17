#include "CameraManager.h"
using namespace glm;
using namespace Managers;

#define ROTATION_SPEED 0.01f


/**
*
*/
CameraManager::CameraManager() 
{
	this->setCameraPosition(glm::vec3(0, 0, -15));
	this->setCameraTarget(glm::vec3(0.0, 0.0, 0.0));
	this->setCameraUp(glm::vec3(0.0, 1.0, 0.0));
	this->upVector = this->cameraUp;
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
glm::vec3 CameraManager::getRightVector()
{
	return normalize(cross(this->upVector, this->cameraPosition - this->cameraTarget));
}

/**
*
*/
glm::vec3 CameraManager::getForwardVector()
{
	return normalize(this->cameraTarget - this->cameraPosition);
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
void CameraManager::lookLeft(float left)
{
	glm::vec3 rVector = this->getRightVector() * left * ROTATION_SPEED;
	std::cout << "lookLeft: x:" << rVector.x << " y:" << rVector.y << " z:" << rVector.z << std::endl;
	this->cameraTarget.x -= rVector.x;
	this->cameraTarget.y -= rVector.y;
	this->cameraTarget.z -= rVector.z;
	this->cameraTarget = normalize(this->cameraTarget-this->cameraPosition)+this->cameraPosition;
}

/**
*
*/
/*void CameraManager::lookRight(float right)
{
	std::cout << "lookRight, calling lookLeft with " << right << std::endl;
	lookLeft(-right);
}*/

/**
*
*/
void CameraManager::lookUp(float value)
{
	glm::vec3 mVector = this->upVector * value * ROTATION_SPEED;
	std::cout << "lookUp: x:" << mVector.x << " y:" << mVector.y << " z:" << mVector.z << std::endl;
	// set the new camera target
	this->cameraTarget.x -= mVector.x;
	this->cameraTarget.y -= mVector.y;
	this->cameraTarget.z -= mVector.z;
	this->cameraTarget = normalize(this->cameraTarget - this->cameraPosition) + this->cameraPosition;
	// set the new upVector
	glm::vec3 rVector = this->getRightVector();
	glm::vec3 fVector = this->getForwardVector();
	this->upVector = normalize(cross(rVector, fVector));
}

/**
*
*/
/*void CameraManager::lookDown(float value)

{
	lookUp(-value);
}*/

/**
*
*/
/*void CameraManager::rotateLeft(float value)

{
	std::cout << "loop left: " << value << std::endl;
}*/

/**
*
*/
/*void CameraManager::rotateRight(float value)
{
	lookLeft(-value);
}*/

/**
*
*/
void CameraManager::panRight(float right)
{
	glm::vec3 rVec = this->getRightVector() * right;
	std::cout << "panRight: x:" << rVec.x << " y:" << rVec.y << " z:" << rVec.z << std::endl;
	this->cameraPosition.x += rVec.x;
	this->cameraPosition.y += rVec.y;
	this->cameraPosition.z += rVec.z;
	this->cameraTarget.x += rVec.x;
	this->cameraTarget.y += rVec.y;
	this->cameraTarget.z += rVec.z;
	//this->cameraPosition.x -= right;
	//this->cameraTarget.x -= right;
}

/**
*
*/
/*void CameraManager::panUp(float up)
{
	std::cout << "panUp: " << up << std::endl;
}*/

/**
*
*/
/*void CameraManager::panDown(float down)
{
	panUp(-down);
}*/

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
	this->cameraTarget.x += direction.x;
	this->cameraTarget.y += direction.y;
	this->cameraTarget.z += direction.z;

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
	//this->rotateRight(dx);
}