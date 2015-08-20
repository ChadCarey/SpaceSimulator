#pragma once
#include "EngineTest.h"
#include "Engine.h"
#include "TSceneListener.h"
using namespace GraphicsEngine;
using namespace EngineInterface;

void EngineTest::run()
{
	ISceneListener* sceneListener = new TSceneListener();

	Engine engine;
	engine.init(sceneListener);

	// start the engine
	engine.run();

	if (sceneListener)
		delete sceneListener;
}