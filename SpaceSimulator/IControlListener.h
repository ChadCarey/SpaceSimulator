
namespace GraphicsEngine
{

	namespace EngineInterface
	{
		class IControlListener
		{
		public:
			virtual void mouseMoveCallback() = 0;
			virtual void mouseDragCallback() = 0;
			virtual void keyboardPressCallback() = 0;
			virtual void keyboardReleaseCallback() = 0;
		};
	}
}