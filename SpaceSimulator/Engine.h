#pragma once
#include "InitGlut.h"
#include "ISceneListener.h"
#include "IControlListener.h"
#include "TextureLoader.h"
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "CameraManager.h"

namespace GraphicsEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		//OpenGL, glut, glew, and manager init
		bool init(EngineInterface::ISceneListener* sceneController, EngineInterface::IControlListener* gameControls);

		// LOOP
		void run();

		// GETTERS
		Managers::ShaderManager* getShaderManager() const;
		Managers::ModelsManager* getModelsManager() const;
		Managers::CameraManager* getCameraManager() const;
		Rendering::TextureLoader* getTextureLoader() const;

		// SETTERS
		void setSceneController(const EngineInterface::ISceneListener*& sceneController);
		void setControlController(const EngineInterface::IControlListener*& gameControls);

	private:
		Managers::ShaderManager* shaderManager;
		Managers::ModelsManager* modelsManager;
		Managers::CameraManager* cameraManager;
		Rendering::TextureLoader* textureLoader;
	};
}