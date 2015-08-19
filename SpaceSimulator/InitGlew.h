#pragma once
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"

/**
* InitGLEW
* handles anything that needs to happen in order to start GLEW
*/
namespace Init
{
		class InitGLEW
		{
		public:
			static void init();
		private:
			static std::string findOpenGLVersion();
		};
}