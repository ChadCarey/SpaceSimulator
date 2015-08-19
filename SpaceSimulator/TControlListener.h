#pragma once
#include "IControlListener.h"


namespace GraphicsEngine
{

	namespace EngineInterface
	{

		class TControlListener : public IControlListener
		{
		public:
			TControlListener();
			virtual void mouseMoveCallback() override;
			virtual void mouseDragCallback() override;
			virtual void keyboardPressCallback() override;
			virtual void keyboardReleaseCallback() override;

		protected:
		};

	}
}