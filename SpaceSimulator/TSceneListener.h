#pragma once
#include "ISceneListener.h"

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
			virtual bool closeCallback() override;
			virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) override;

			virtual void mouseMoveCallback() override;
			virtual void mouseDragCallback() override;
			virtual void keyboardPressCallback() override;
			virtual void keyboardReleaseCallback() override;
		private:
			Managers::ModelsManager modelsManager;
		};
	}
}