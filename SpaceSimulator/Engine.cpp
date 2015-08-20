#include "Engine.h"
using namespace GraphicsEngine;
using namespace Init;

Engine::Engine()
{

}

//You can set params for init
bool Engine::init(EngineInterface::ISceneListener* sceneController)
{
	WindowInfo window(std::string("in2gpu OpenGL Chapter 2 tutorial"), 400, 200, 800, 600, true);
	ContextInfo context(4, 2, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	InitGLUT::init(window, context, frameBufferInfo);
		
	InitGLUT::setListener(sceneController);

	return true;
}

//Create the loop
void Engine::run()
{
	InitGLUT::run();
}