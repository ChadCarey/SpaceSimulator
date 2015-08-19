#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "CameraManager.h"
#include "TextureLoader.h"

/**
* 
* Uses the glutTimerFunc as a scheduler for timed game events
*/

namespace GraphicsEngine
{
	namespace EngineInterface
	{

		class IEventScheduler
		{
		public:
			void scheduleEvent();
			virtual void systemEvents() = 0;

			// SETTERS
			void setManagers(Managers::CameraManager* cameraManager, Managers::ModelsManager* modelsManager, Managers::ShaderManager* shaderManager, Rendering::TextureLoader* textureLoader);

		protected:
			Managers::ShaderManager* shaderManager;
			Managers::ModelsManager* modelsManager;
			Managers::CameraManager* cameraManager;
			Rendering::TextureLoader* textureLoader;
		};
	}
}