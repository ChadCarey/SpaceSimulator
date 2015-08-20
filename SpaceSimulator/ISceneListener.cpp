#include "ISceneListener.h"
using namespace GraphicsEngine::EngineInterface;

Managers::CameraManager ISceneListener::cameraManager;

ISceneListener::ISceneListener()
{
	projectionMatrix = glm::mat4(0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0);
}

ISceneListener::~ISceneListener() {}