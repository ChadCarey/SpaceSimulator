#pragma once
#include "ModelsManager.h"
#include "CameraManager.h"

/**
* 
*
*/

namespace GraphicsEngine
{

	namespace EngineInterface
	{

		class ISceneListener
		{
		public:
			ISceneListener();
			~ISceneListener();

			// events
			virtual void beginFrameCallback() = 0;
			virtual void drawFrameCallback() = 0;
			virtual void endFrameCallback() = 0;
			virtual bool closeCallback() = 0;
			virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) = 0;

			// controls
			virtual void mouseMoveCallback(int x, int y, int centerX, int centerY) = 0;
			virtual void mouseDragCallback(int x, int y, int centerX, int centerY) = 0;
			virtual void mouseClickCallback(int a, int b, int c, int d) = 0;
			virtual void keyboardPressCallback(const unsigned char& letter, const int& a, const int& b) = 0;
			virtual void keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b) = 0;

		protected:
			static Managers::CameraManager cameraManager;
			glm::mat4 projectionMatrix;
		};
	}
}