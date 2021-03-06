#include "Engine.h"
using namespace GraphicsEngine;
using namespace EngineInterface;
using namespace Init;

#define ESC_KEY 27

// statics
WindowInfo Engine::windowInformation;
ISceneListener* Engine::sceneListener = NULL;
int Engine::windowCenterX = 0;
int Engine::windowCenterY = 0;

Engine::Engine()
{

}

//You can set params for init
bool Engine::init()
{
	WindowInfo window("Space Simulator", 400, 200, 800, 600, true);
	ContextInfo context(4, 2, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	initGLUT(window, context, frameBufferInfo);

	return true;
}

//Create the loop
void Engine::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}


void Engine::initGLUT(const Init::WindowInfo& windowInfo, const Init::ContextInfo& contextInfo, const Init::FramebufferInfo& framebufferInfo)
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
	glEnable(GL_DEPTH_TEST);

	// scene callbacks
	setCallbacks();
	
	initGLEW();

	// debug callback functions ( must be done after InitGLEW::Init() )
	glDebugMessageCallback(DebugOutput::callback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);


	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	windowInformation = windowInfo;

	printOpenGLInfo(windowInfo, contextInfo);

}


void Engine::setSceneManager(ISceneListener* newSceneListener)
{
	sceneListener = newSceneListener;
}


/**
* printOpenGLInfo
* display info about the initilization of openGL and glut
*/
void Engine::printOpenGLInfo(const Init::WindowInfo& windowInfo, const Init::ContextInfo& contextInfo)
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

void Engine::initGLEW()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}

	std::cout << findOpenGLVersion().c_str() << std::endl;
}


/**
* FindOpenGLVersion
* this will find the supported openGL version for the pc
*/
std::string Engine::findOpenGLVersion()
{
	std::string version = "none";

	if (glewIsSupported("GL_VERSION_4_5"))
	{
		version = "GL_VERSION_4_5";
	}
	else if (glewIsSupported("GL_VERSION_4_4"))
	{
		version = "GL_VERSION_4_4";
	}
	else if (glewIsSupported("GL_VERSION_4_3"))
	{
		version = "GL_VERSION_4_3";
	}
	else if (glewIsSupported("GL_VERSION_4_2"))
	{
		version = "GL_VERSION_4_2";
	}
	else if (glewIsSupported("GL_VERSION_4_1"))
	{
		version = "GL_VERSION_4_1";
	}
	else if (glewIsSupported("GL_VERSION_4_0"))
	{
		version = "GL_VERSION_4_0";
	}
	return version;
}



/******************** CALLBACKS *********************/


void Engine::setCallbacks()
{
	// display
	glutIdleFunc(idleCallback); // called when events are not being received.
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback); // triggered when the window is reshaped

	// keyboard
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);

	// mouse
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMotionFunc(mouseDrag);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
}

void Engine::idleCallback(void)
{
	// just redisplay
	glutPostRedisplay();
}

void Engine::displayCallback()
{
	//check for NULL
	if (sceneListener)
	{
		sceneListener->beginFrameCallback();
		// now draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		sceneListener->drawFrameCallback();

		glutSwapBuffers();

		sceneListener->endFrameCallback();
	}
}

void Engine::reshapeCallback(int width, int height)
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

void Engine::closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Engine::enterFullscreen()
{
	glutFullScreen();
}

void Engine::exitFullscreen()
{
	glutLeaveFullScreen();
}


void Engine::mouseMove(int x, int y)
{
	if (sceneListener)
	{
		int centerx = windowInformation.width / 2;
		int centery = windowInformation.height / 2;
		if (!warped(x, y, centerx, centery))
		{
			sceneListener->mouseMoveCallback(x, y, centerx, centery);
			// now warp the pointer back to the center of the screen
			//warped = true;
			glutWarpPointer(centerx, centery);
		}
	}
}

void Engine::mouseDrag(int x, int y)
{
	if (sceneListener)
	{
		int centerx = windowInformation.width / 2;
		int centery = windowInformation.height / 2;
		if (!warped(x, y, centerx, centery))
			sceneListener->mouseDragCallback(x, y, centerx, centery);
	}
}

void Engine::mouseClick(int a, int b, int c, int d)
{
	if (sceneListener)
		sceneListener->mouseClickCallback(a, b, c, d);
}

void Engine::keyDown(unsigned char ch, int a, int b)
{
	if (ch == ESC_KEY)
		Engine::closeCallback();

	if (sceneListener)
		sceneListener->keyboardPressCallback(ch, a, b);
}

void Engine::keyUp(unsigned char ch, int a, int b)
{
	if (sceneListener)
		sceneListener->keyboardReleaseCallback(ch, a, b);
}

void Engine::specialKeyDown(int a, int b, int c)
{
	//if (sceneListener)
		//sceneListener->specialKey();
}

