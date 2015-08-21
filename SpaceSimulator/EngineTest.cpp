#pragma once
#include "EngineTest.h"
#include "Engine.h"
#include "TSceneListener.h"
using namespace GraphicsEngine;
using namespace EngineInterface;

void EngineTest::run()
{
	Engine engine;
	engine.init();
	ISceneListener* sceneListener = new TSceneListener();
	engine.setSceneManager(sceneListener);

	// start the engine
	engine.run();

	if (sceneListener)
		delete sceneListener;
}