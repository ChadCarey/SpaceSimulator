#pragma once
#include "EngineTest.h"
#include "Engine.h"
#include "ISceneListener.h"
#include "IControlListener.h"

#include "TSceneListener.h"
#include "TControlListener.h"
#include "ModelsManager.h"
#include "TexturedCube.h"
using namespace GraphicsEngine;
using namespace EngineInterface;
using namespace Managers;
using namespace Rendering;

void EngineTest::run()
{
	ISceneListener* sceneListener = new TSceneListener();
	IControlListener* controlListener = new TControlListener();

	GraphicsEngine::Engine engine;
	engine.init(sceneListener, controlListener);
	ModelsManager* models = engine.getModelsManager();

	// create the shader program for textured objects
	engine.getShaderManager()->createProgram("TextureShader", "Texture_Vertex_Shader.glsl", "Texture_Fragment_Shader.glsl");
	// create the cube object
	TexturedCube* cube = new TexturedCube(); // models manager will delete the models, I may want to change this
	int program = engine.getShaderManager()->getShader("TextureShader");
	if (program != 0)
		cube->setProgram(program);
	else
	{
		std::cout << "Error loading program\n";
		return;
	}
	// load texture
	unsigned int texture = engine.getTextureLoader()->loadTexture("Crate.bmp", 256, 256);
	cube->setTexture("Crate", texture);
	models->push_front(cube);

	// start the engine
	engine.run();

	if (sceneListener)
		delete sceneListener;
	if (controlListener)
		delete controlListener;
}