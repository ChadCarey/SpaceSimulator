#include "Model.h"
using namespace Rendering;

TextureLoader Model::textureLoader;
Managers::ShaderManager Model::shaderManager;

Model::Model() 
{
	position = glm::vec3(0.0, 0.0, 0.0);
}

Model::~Model()
{
	destroy();
}

void Model::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {}

void Model::update() {}

void Model::setProgram(GLuint program)
{
	if(program != 0)
		this->program = program;
}

GLuint Model::getVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::getVbos() const
{
	return vbos;
}

const GLuint Model::getTexture(std::string textureName) const
{
	return textures.at(textureName);
}

void Model::setTexture(std::string textureName, GLuint texture)
{
	if (texture != 0) 
		textures[textureName] = texture;
}


void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();

	if (textures.size() > 0)
	{
		for (auto t: textures)
		{
			glDeleteTextures(1, &t.second);
		}
		textures.clear();
	}
}

void Model::rotate(const glm::vec3& rotate)
{
	this->rotation += rotate;
}

void Model::rotate(float x, float y, float z)
{
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
}

void Model::move(const glm::vec3& dVector)
{
	this->position += dVector;
}

void Model::move(float x, float y, float z)
{
	std::cout << "position.x: " << this->position.x << std::endl;
	this->position.x += x;
	std::cout << "position.x+x: " << this->position.x << std::endl;

	std::cout << "position.y: " << this->position.y << std::endl;
	this->position.y += y;
	std::cout << "position.y+y: " << this->position.y << std::endl;

	std::cout << "position.z: " << this->position.z << std::endl;
	this->position.z += z;
	std::cout << "position.z+z: " << this->position.z << std::endl;
}


void Model::setPosition(const glm::vec3& newPosition)
{
	this->position = newPosition;
}

void Model::setPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Model::setRotation(const glm::vec3& newRotation)
{
	this->rotation = newRotation;
}

void Model::setRotation(float x, float y, float z)
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
}
