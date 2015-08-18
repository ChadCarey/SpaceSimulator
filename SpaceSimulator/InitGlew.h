#pragma once
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"

namespace Init
{
		class InitGLEW
		{
		public:
			static void Init();
		private:
			static std::string findOpenGLVersion();
		};
}