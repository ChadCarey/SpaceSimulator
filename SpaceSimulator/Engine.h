#pragma once
#include "InitGlut.h"
#include "ISceneListener.h"

namespace GraphicsEngine
{
	class Engine
	{

	public:
		Engine();

		//OpenGL, glut, glew, and manager init
		bool init(EngineInterface::ISceneListener* sceneController);

		// LOOP
		void run();
	};
}