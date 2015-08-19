#pragma once
#include "IEventScheduler.h"
using namespace GraphicsEngine::EngineInterface;

void IEventScheduler::setManagers(Managers::CameraManager* cameraManager, Managers::ModelsManager* modelsManager, Managers::ShaderManager* shaderManager, Rendering::TextureLoader* textureLoader)
{
	this->cameraManager = cameraManager;
	this->modelsManager = modelsManager;
	this->shaderManager = shaderManager;
	this->textureLoader = textureLoader;
}

void IEventScheduler::scheduleEvent()
{

}