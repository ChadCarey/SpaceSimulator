#include "Engine.h"
using namespace GraphicsEngine;
using namespace Init;

Engine::Engine()
{

}

//You can set params for init
bool Engine::init(EngineInterface::ISceneListener* sceneController, EngineInterface::IControlListener* gameControls)
{
	WindowInfo window(std::string("in2gpu OpenGL Chapter 2 tutorial"), 400, 200, 800, 600, true);
	ContextInfo context(4, 2, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	InitGLUT::init(window, context, frameBufferInfo);
		
	InitGLUT::setListeners(sceneController, gameControls);
	
	// Create the game managers and texture loader
	shaderManager = new Managers::ShaderManager();
	shaderManager->createProgram("textureShader", "Texture_Vertex_Shader.glsl", "Texture_Fragment_Shader.glsl");
	textureLoader = new TextureLoader();	
	modelsManager = new Managers::ModelsManager();
	cameraManager = new Managers::CameraManager();

	// give the controll listeners and eventSchedualer access to the same managers
	sceneController->setManagers(cameraManager, modelsManager, shaderManager, textureLoader);
	gameControls->setManagers(cameraManager, modelsManager, shaderManager, textureLoader);

	return true;
}

//Create the loop
void Engine::run()
{
	InitGLUT::run();
}

Managers::ShaderManager* Engine::getShaderManager() const
{
	return shaderManager;
}

Managers::ModelsManager* Engine::getModelsManager() const
{
	return modelsManager;
}

TextureLoader* Engine::getTextureLoader() const
{
	return textureLoader;
}

Engine::~Engine()
{
	if (shaderManager)
		delete shaderManager;

	if (textureLoader)
		delete textureLoader;

	if (modelsManager)
		delete modelsManager;

	if (cameraManager)
		delete cameraManager;
}