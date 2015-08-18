#include "CameraManager.h"
using namespace glm;
using namespace Managers;

CameraManager* CameraManager::instance = NULL;

CameraManager::CameraManager() 
{
	//glutIgnoreKeyRepeat(1);
	//glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(pressKey);
	//glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	//glutMouseFunc(mouseButton);
	//glutMotionFunc(mouseMove);
}

CameraManager* CameraManager::getInstance()
{
	if (instance == NULL)
		instance = new CameraManager();
	return instance;
}

glm::mat4 CameraManager::LookAt(vec3& position, //camera position (eye)
	vec3& target,  //camera target
	vec3& up)
{
	return glm::lookAt(position, target, up);
}