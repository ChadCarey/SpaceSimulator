#include "Model.h"
using namespace Models;

Model::Model() 
{
	position_vector = glm::vec3(0.0, 0.0, 0.0);
}

Model::~Model()
{
	Destroy();
}

void Model::Draw() {}

void Model::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {}

void Model::Update() {}

void Model::SetProgram(GLuint program)
{
	if(program != 0)
		this->program = program;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

const GLuint Model::GetTexture(std::string textureName) const
{
	return textures.at(textureName);
}

void Model::SetTexture(std::string textureName, GLuint texture)
{
	if (texture == 0) 
		return;
	textures[textureName] = texture;
}


void Model::Destroy()
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
