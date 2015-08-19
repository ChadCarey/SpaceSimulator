#include "InitGlut.h"

using namespace Init;
using namespace GraphicsEngine::EngineInterface;

// statics
WindowInfo InitGLUT::windowInformation;
ISceneListener* InitGLUT::sceneListener = NULL;
IControlListener* InitGLUT::controlListener = NULL;

void InitGLUT::init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FramebufferInfo& framebufferInfo)
{
	int dummyargc = 1;
	char *dummyargv[] = { "Space Simulator", NULL };
	glutInit(&dummyargc, dummyargv);

	if (contextInfo.core)
	{
		std::cout << "Setting context version to" << contextInfo.major_version << "." << contextInfo.minor_version << std::endl;
		glutInitContextVersion(contextInfo.major_version, contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		// this puts glut into compatability mode so that the version doesn't matter
		// this only works within a core contex mode
		std::cout << "Setting context version to compatability mode\n";
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	std::cout << "window position x: " << windowInfo.position_x << std::endl;
	std::cout << "window position y: " << windowInfo.position_y << std::endl;
	std::cout << "window width: " << windowInfo.width << std::endl;
	std::cout << "window height: " << windowInfo.height << std::endl;
	std::cout << "window name: " << windowInfo.name.c_str() << std::endl;

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	// sets the window name
	glutCreateWindow(windowInfo.name.c_str()); 

	std::cout << "GLUT:initialized" << std::endl;
	// enables debug messages from OpenGL and shader programs ( must be done after glutCreateWindow() )
	glEnable(GL_DEBUG_OUTPUT); 

	// scene callbacks
	glutIdleFunc(idleCallback); // called when events are not being received.
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback); // triggered when the window is reshaped

	// control callbacks
		// TODO

	InitGLEW::init();

	// debug callback functions ( must be done after InitGLEW::Init() )
	glDebugMessageCallback(DebugOutput::callback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);


	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	windowInformation = windowInfo;

	printOpenGLInfo(windowInfo, contextInfo);

}

/**
* run
* starts the GLUT main loop
*/
void InitGLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

/**
* setListeners
* sets the sceneListener and controlListener that is to be used by GLUT
*/
void InitGLUT::setListeners(ISceneListener* newSceneListener, IControlListener* newControlListener)
{
	sceneListener = newSceneListener;
	controlListener = newControlListener;
}

/**
* printOpenGLInfo
* display info about the initilization of openGL and glut
*/
void InitGLUT::printOpenGLInfo(const Init::WindowInfo& windowInfo, const Init::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "************************** GLUT INFO *******************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}

void InitGLUT::idleCallback(void)
{
	// just redisplay
	glutPostRedisplay();
}

void InitGLUT::displayCallback()
{
	//check for NULL
	if (sceneListener)
	{
		sceneListener->beginFrameCallback();
		sceneListener->drawFrameCallback();

		glutSwapBuffers();

		sceneListener->endFrameCallback();
	}
}

void InitGLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (sceneListener)
		{
			sceneListener->windowReshapeCallback(width, height, windowInformation.width, windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void InitGLUT::closeCallback()
{
	if (sceneListener)
	{
		if (sceneListener->closeCallback())
		{
			std::cout << "GLUT:\t Finished" << std::endl;
			glutLeaveMainLoop();
		}
	}
}

void InitGLUT::enterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}
