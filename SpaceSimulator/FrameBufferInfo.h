#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"

namespace Init
{

	struct FramebufferInfo
	{

		unsigned int flags;
		bool msaa;//to enable or disable it when wee need it

		FramebufferInfo()
		{
			//default, the | bit ORs the values to get a bitstring of options
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaa = false;
		}

		FramebufferInfo(bool color, bool depth, bool stencil, bool msaa)
		{
			// this keeps track of what options have been selected
			flags = GLUT_DOUBLE;
			if (color)
				flags |= GLUT_RGBA | GLUT_ALPHA;
			if (depth)
				flags |= GLUT_DEPTH;
			if (stencil)
				flags |= GLUT_STENCIL;
			if (msaa)
				flags |= GLUT_MULTISAMPLE;
			this->msaa = msaa;
		}

		FramebufferInfo(const FramebufferInfo& origonal)
		{
			this->flags = origonal.flags;
			this->msaa = origonal.msaa;
		}

		FramebufferInfo& operator=(const FramebufferInfo& origonal)
		{
			this->flags = origonal.flags;
			this->msaa = origonal.msaa;
		}
	};
}