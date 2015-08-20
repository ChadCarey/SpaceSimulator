#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "CameraManager.h"
#include "TextureLoader.h"

/**
* 
*
*/

namespace GraphicsEngine
{

	namespace EngineInterface
	{

		class ISceneListener
		{
		public:
			ISceneListener();

			virtual void beginFrameCallback() = 0;
			virtual void drawFrameCallback() = 0;
			virtual void endFrameCallback() = 0;
			virtual bool closeCallback() = 0;
			virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) = 0;

			// SETTERS
			void setManagers(Managers::CameraManager* cameraManager, Managers::ModelsManager* modelsManager, Managers::ShaderManager* shaderManager, Rendering::TextureLoader* textureLoader);

		protected:
			Managers::ShaderManager* shaderManager;
			Managers::ModelsManager* modelsManager;
			Managers::CameraManager* cameraManager;
			Rendering::TextureLoader* textureLoader;
			glm::mat4 projectionMatrix;
		};
	}
}