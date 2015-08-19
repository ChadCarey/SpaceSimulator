#pragma once
#include "EngineTest.h"
#include "Engine.h"
#include "ISceneListener.h"
#include "IControlListener.h"
#include "IEventScheduler.h"

#include "TSceneListener.h"
#include "TControlListener.h"
#include "TEventScheduler.h"
using namespace GraphicsEngine;
using namespace EngineInterface;

void EngineTest::run()
{
	ISceneListener* sceneListener = new TSceneListener();
	IControlListener* controlListener = new TControlListener();
	IEventScheduler* eventScheduler = new TEventScheduler();

	GraphicsEngine::Engine engine;
	engine.init(sceneListener, controlListener, eventScheduler);
	engine.run();

	if (sceneListener)
		delete sceneListener;
	if (controlListener)
		delete controlListener;
	if (eventScheduler)
		delete eventScheduler;
}