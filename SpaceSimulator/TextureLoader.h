#pragma once
#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include "BMPHeaders.h"

namespace Rendering
{
	class TextureLoader
	{
		public:
			TextureLoader();
			~TextureLoader();

			unsigned int loadTexture(const std::string& filename, unsigned int width, unsigned int height);

		private:
			void loadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
	};
}
