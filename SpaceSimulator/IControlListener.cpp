#include "IControlListener.h"
using namespace GraphicsEngine::EngineInterface;

void IControlListener::setManagers(Managers::CameraManager* cameraManager, Managers::ModelsManager* modelsManager, Managers::ShaderManager* shaderManager, Rendering::TextureLoader* textureLoader)
{
	this->cameraManager = cameraManager;
	this->modelsManager = modelsManager;
	this->shaderManager = shaderManager;
	this->textureLoader = textureLoader;
}