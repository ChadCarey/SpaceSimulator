#pragma once

/**
* ref: http://in2gpu.com/2015/03/04/create-a-game-engine-part-iv-scene-manager/
*		"...passing SceneManager to Init_GLUT as a parameter is a bad practice because it creates an ugly dependency 
*		(maybe in the future we will want other scenes and/or other object to be notified). So it’s much better if 
*		we inject an interface in Init_GLUT and SceneManager implements this interface."
*/

namespace GraphicsEngine
{

	namespace EngineInterface
	{

		class ISceneListener
		{
		public:
			virtual ~ISceneListener() = 0;

			virtual void beginFrameCallback() = 0; // physics time
			virtual void drawFrameCallback() = 0; // drawing time
			virtual void endFrameCallback() = 0;
			virtual void idleCallback() = 0;
			virtual void timerCallback() = 0;
			virtual void windowReshapeCallback(int width,
				int height,
				int previous_width,
				int previous_height) = 0;
		};

		inline ISceneListener::~ISceneListener(){
			//implementation of pure virtual destructor
		}
	}
}