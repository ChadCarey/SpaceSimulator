#include "Model.h"
using namespace Rendering;

#define PI 3.14159265
TextureLoader Model::textureLoader;
Managers::ShaderManager* Model::shaderManager = NULL;
long long int Model::modelCount = 0;

std::map<std::string, GLuint> Model::textures;

Model::Model() 
{
	if (shaderManager == NULL)
		shaderManager = new Managers::ShaderManager();
	modelCount++;
	position = glm::vec3(0.0, 0.0, 0.0);
}

Model::~Model()
{
	modelCount--;
	if (modelCount < 1)
		delete shaderManager;
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
    if (textures.find(textureName) != textures.end())
    {
        return textures.at(textureName);
    }
    else
    {
        std::cout << "Texture not yet found. Generating texture.\n";
        return 0;
    }
}

void Model::setTexture(std::string textureFileName, int height, int width)
{
	GLuint texture = this->textureLoader.loadTexture(textureFileName, width, height);
	if (texture != 0)
	{
		textures[textureFileName] = texture;
	}
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

void Model::rotate(float x, float y, float z)
{
	float ratio = (PI / 180);
	this->rotation.x += x*ratio;
	this->rotation.y += y*ratio;
	this->rotation.z += z*ratio;
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
	this->position.x = newPosition.x;
	this->position.y = newPosition.y;
	this->position.z = newPosition.z;
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
	float ratio = PI / 180;
	this->rotation.x = x*ratio;
	this->rotation.y = y*ratio;
	this->rotation.z = z*ratio;
}

glm::vec3 Model::getPosition() const
{
	return this->position;
}