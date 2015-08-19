#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "CameraManager.h"
#include "TextureLoader.h"

namespace GraphicsEngine
{

	namespace EngineInterface
	{
		class IControlListener
		{
		public:
			virtual void mouseMoveCallback() = 0;
			virtual void mouseDragCallback() = 0;
			virtual void keyboardPressCallback() = 0;
			virtual void keyboardReleaseCallback() = 0;

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