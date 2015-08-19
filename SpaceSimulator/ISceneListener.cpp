#include "ISceneListener.h"
using namespace GraphicsEngine::EngineInterface;

ISceneListener::ISceneListener()
{
	projectionMatrix = glm::mat4(0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0);
}

void ISceneListener::setManagers(Managers::CameraManager* cameraManager, Managers::ModelsManager* modelsManager, Managers::ShaderManager* shaderManager, Rendering::TextureLoader* textureLoader)
{
	this->cameraManager = cameraManager;
	this->modelsManager = modelsManager;
	this->shaderManager = shaderManager;
	this->textureLoader = textureLoader;
}