#pragma once
#include "WindowInfo.h"
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "DebugOutput.h"
#include "ISceneListener.h"

namespace GraphicsEngine
{
	class Engine
	{

	public:
		Engine();

		//OpenGL, glut, glew, and manager init
		bool init();
		void setSceneManager(GraphicsEngine::EngineInterface::ISceneListener*);
		void run();

		static void enterFullscreen();
		static void exitFullscreen();
		static void printOpenGLInfo(const Init::WindowInfo& windowInfo, const Init::ContextInfo& context);

	private:
		// GLUT
		static void initGLUT(const Init::WindowInfo& window,
			const Init::ContextInfo& context,
			const Init::FramebufferInfo& framebufferInfo);
		// GLUT variables
		static GraphicsEngine::EngineInterface::ISceneListener* sceneListener;
		static Init::WindowInfo windowInformation;

		// SCENE CALLBACK METHODS
		static void setCallbacks();
		static void idleCallback(void);
		static void displayCallback(void);
		static void reshapeCallback(int width, int height);
		static void closeCallback();

		// CONTROL CALLBACK METHODS
		static void mouseMove(int x, int y);
		static void mouseDrag(int x, int y);
		static void mouseClick(int a, int b, int c, int d);
		static void keyDown(unsigned char ch, int a, int b);
		static void keyUp(unsigned char ch, int a, int b);
		static void specialKeyDown();


		// GLEW
		static void initGLEW();
		static std::string findOpenGLVersion();
	};
}