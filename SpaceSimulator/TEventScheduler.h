#pragma once
#include "IEventScheduler.h"

namespace GraphicsEngine
{

	namespace EngineInterface
	{
		class TEventScheduler : public IEventScheduler
		{
		public:
			TEventScheduler();
			void event1();
			virtual void systemEvents() override;
		protected:
		};
	}
}