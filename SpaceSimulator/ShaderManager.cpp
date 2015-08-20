#include "ShaderManager.h"
using namespace Managers;

std::map<std::string, GLuint> ShaderManager::shaderPrograms; // look up why this is needed for it to work

ShaderManager::ShaderManager(void){}

ShaderManager::~ShaderManager(void)
{
	std::map<std::string, GLuint>::iterator i;
	for (i = shaderPrograms.begin(); i != shaderPrograms.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	shaderPrograms.clear();
}

std::string ShaderManager::readShader(const std::string filename)
{

	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{


	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);

	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();
	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint ShaderManager::createProgram(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	std::string shaderName = vertexShaderFilename + "_" + fragmentShaderFilename;

	GLuint program = this->getShader(shaderName);
	if (program != 0)
		return program;

	//read the shader files and save the code
	std::string vertex_shader_code = readShader(vertexShaderFilename.c_str());
	std::string fragment_shader_code = readShader(fragmentShaderFilename.c_str());

	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	
	shaderPrograms[shaderName] = program;
	return program;
}

const GLuint ShaderManager::getShader(const std::string& shaderName) throw (std::string)
{
	GLuint pro = 0;
	try
	{
		pro = shaderPrograms.at(shaderName);
	}
	catch (std::out_of_range& oor)
	{	}
	return pro;
}

void ShaderManager::deleteShader(const std::string& shaderName)
{
	try
	{
		shaderPrograms.erase(shaderName);
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "ShaderManager::DeleteShader: Shader not found, could not be deleted\n";
	}
}
