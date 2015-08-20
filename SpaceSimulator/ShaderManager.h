#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

/**
*
* Resources: http://in2gpu.com/2014/10/29/shaders-basics/
*/
namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();
		GLuint createProgram(const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
		static const GLuint ShaderManager::getShader(const std::string& shaderName) throw (std::string);
		static void ShaderManager::deleteShader(const std::string& shaderName);

	private:
		std::string readShader(const std::string filename);
		GLuint createShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
		static std::map<std::string, GLuint> shaderPrograms;
	};
}
