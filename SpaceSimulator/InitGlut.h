#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "InitGlew.h"
#include "ISceneListener.h"
#include "IControlListener.h"
#include "DebugOutput.h"

/**
* InitGLUT
*/
namespace Init
{
		class InitGLUT{

		public:
			// GETTERS

			// SETTERS
			static void setListeners(GraphicsEngine::EngineInterface::ISceneListener* sceneListener, GraphicsEngine::EngineInterface::IControlListener* controlListener);

			// METHODS
			static void init(const Init::WindowInfo& window,
				const Init::ContextInfo& context,
				const Init::FramebufferInfo& framebufferInfo);
			static void run(); // this is the main run function
			static void enterFullscreen();
			static void exitFullscreen();
			static void printOpenGLInfo(const Init::WindowInfo& windowInfo, const Init::ContextInfo& context);
		private:
			// VARIABLES
			static bool drawn;
			static GraphicsEngine::EngineInterface::ISceneListener* sceneListener;
			static GraphicsEngine::EngineInterface::IControlListener* controlListener;
			static Init::WindowInfo windowInformation;

			// SCENE CALLBACK METHODS
			static void idleCallback(void);
			static void displayCallback(void);
			static void reshapeCallback(int width, int height);
			static void closeCallback();

			// CONTROL CALLBACK METHODS
			static void mouseMove();
			static void mouseDrag();
			static void mouseClick();
			static void keyDown();
			static void keyUp();
			static void specialKeyDown();
		};
}