#pragma once
#include "SpaceSimulator.h"
#include "Engine.h"
#include "SpaceListener.h"
using namespace GraphicsEngine;
using namespace EngineInterface;

void SpaceSimulator::run()
{
	Engine* engine = new Engine();
	engine->init();
	ISceneListener* sceneListener = new SpaceListener();
	engine->setSceneManager(sceneListener);

	// start the engine
	engine->run();

	if (sceneListener)
		delete sceneListener;
	if (engine)
		delete engine;
}