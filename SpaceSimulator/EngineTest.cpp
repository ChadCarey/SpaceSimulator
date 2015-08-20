#pragma once
#include "EngineTest.h"
#include "Engine.h"
#include "ISceneListener.h"
#include "IControlListener.h"

#include "TSceneListener.h"
#include "TControlListener.h"
using namespace GraphicsEngine;
using namespace EngineInterface;

void EngineTest::run()
{
	ISceneListener* sceneListener = new TSceneListener();
	IControlListener* controlListener = new TControlListener();

	GraphicsEngine::Engine engine;
	engine.init(sceneListener, controlListener);
	engine.run();

	if (sceneListener)
		delete sceneListener;
	if (controlListener)
		delete controlListener;
}