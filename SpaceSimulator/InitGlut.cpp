#include "InitGlut.h"

using namespace Core;

// statics
Core::IListener* Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FramebufferInfo& framebufferInfo)
{
	// dummy args
	int fakeargc = 1;
	char *fakeargv[] = { "dummy", NULL };
	glutInit(&fakeargc, fakeargv);

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

	std::cout << "x: " << windowInfo.position_x << std::endl;
	std::cout << "y: " << windowInfo.position_y << std::endl;
	std::cout << "width: " << windowInfo.width << std::endl;
	std::cout << "height: " << windowInfo.height << std::endl;
	std::cout << "name: " << windowInfo.name.c_str() << std::endl;

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);


	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;
	glEnable(GL_DEBUG_OUTPUT); // enables debug messages from OpenGL and shader programs ( must be done after glutCreateWindow() )

	// callbacks
	glutIdleFunc(idleCallback); // called when events are not being received.
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback); // triggered when the window is reshaped

	InitGLEW::Init();

	// debug callback functions ( must be done after InitGLEW::Init() )
	glDebugMessageCallback(DebugOutput::Callback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);


	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	windowInformation = windowInfo;

	printOpenGLInfo(windowInfo, contextInfo);

}

//starts the rendering Loop
void Init_GLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo)
{

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}



void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	//check for NULL
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width, height, windowInformation.width, windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Init_GLUT::closeCallback()
{
	close();
}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::setListener(Core::IListener*& iListener)
{
	listener = iListener;
}
