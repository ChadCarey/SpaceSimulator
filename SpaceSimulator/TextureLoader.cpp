#include "TextureLoader.h"
using namespace Rendering;

// these are the files that the loadCubemapTexture method is expecting
const std::string cubemapFiles[] = { "px.bmp", "nx.bmp", "py.bmp", "ny.bmp", "pz.bmp", "nz.bmp" };

TextureLoader::TextureLoader() {}

TextureLoader::~TextureLoader() {}

unsigned int TextureLoader::loadTexture(const std::string& filename, unsigned int width, unsigned int height)
{

	unsigned char* data;
	loadBMPFile(filename, width, height, data);

	// create the OpenGL texture
	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);

	// These are for filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	// this is for when the texture is not divisable by 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generates texture once all parameters have been set
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;

	// creates the mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	return gl_texture_object;
}

/*
* This will load a cubemap from the specified folder
* NOTE: this method will be looking for the following files in the folder
* "px.bmp", "nx.bmp", "py.bmp", "ny.bmp", "pz.bmp", "nz.bmp"
* all file must be found and be 24 bit bmps
*/
unsigned int TextureLoader::loadCubemapTexture(const std::string& folderName, unsigned int size)
{    
    // create the OpenGL texture
    unsigned int gl_texture_object;
    glGenTextures(1, &gl_texture_object);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gl_texture_object);

    // load all images from the folder
    for (int i = 0; i < 6; ++i)
    {
        unsigned char* data;
        std::string filename = folderName + cubemapFiles[i];
        std::cout << filename << std::endl;
        loadBMPFile(filename, size, size, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        delete data;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// creates the mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	return gl_texture_object;
}


void TextureLoader::loadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data)
{
	// read the file
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()){
		std::cout << "Texture Loader: Cannot open texture file ";
		width = 0;
		height = 0;
		return;
	}

    // read headers
	Texture::BMP_Header h; Texture::BMP_Header_Info h_info;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.f_lenght), sizeof(int));
	file.read((char*)&(h.rezerved1), sizeof(short));
	file.read((char*)&(h.rezerved2), sizeof(short));
	file.read((char*)&(h.offBits), sizeof(int));
	file.read((char*)&(h_info), sizeof(Texture::BMP_Header_Info));

    // create the memory
	data = new unsigned char[h_info.width*h_info.height * 3];

	// check if the line contains 4 byte groups
	long padd = 0;
	if ((h_info.width * 3) % 4 != 0) padd = 4 - (h_info.width * 3) % 4;

	width = h_info.width;
	height = h_info.height;

	long pointer;
	unsigned char r, g, b;

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}
