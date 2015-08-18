#include "InitGlew.h"
using namespace Core;

std::string InitGLEW::findOpenGLVersion()
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


void InitGLEW::Init()
{

	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}

	std::cout << findOpenGLVersion().c_str() << std::endl;
}
