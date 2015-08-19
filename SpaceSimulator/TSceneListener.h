#pragma once
#include "ISceneListener.h"

#define FPS 40

/**
* TSceneListener extends IListener
*/
namespace GraphicsEngine
{

	namespace EngineInterface
	{

		class TSceneListener : public ISceneListener
		{
		public:
			TSceneListener();
			~TSceneListener();

			virtual void beginFrameCallback() override;
			virtual void drawFrameCallback() override;
			virtual void endFrameCallback() override;
			virtual void startTimer(int miliseconds) override;
			virtual void timerCallback(int value) override;
			virtual bool closeCallback() override;
			virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) override;
		};
	}
}