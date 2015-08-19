#pragma once

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
			virtual ~ISceneListener() = 0;

			virtual void beginFrameCallback() = 0;
			virtual void drawFrameCallback() = 0;
			virtual void endFrameCallback() = 0;
			virtual void startTimer(int miliseconds) = 0;
			virtual void timerCallback(int value) = 0;
			virtual bool closeCallback() = 0;
			virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) = 0;
		};

		inline ISceneListener::~ISceneListener(){
			//implementation of pure virtual destructor
		}
	}
}