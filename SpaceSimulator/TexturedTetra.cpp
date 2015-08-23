#include "TexturedTetra.h"
using namespace Rendering;

#define PI 3.14159265
#define VERTEX_SHADER "Texture_Vertex_Shader.glsl"
#define FRAGMENT_SHADER "Texture_Fragment_Shader.glsl"
#define TEXTURE "Crate.bmp"
#define TEXTURE_SIZE 256

TexturedTetra::TexturedTetra(float scale)
{
	this->setProgram(shaderManager->createProgram(VERTEX_SHADER, FRAGMENT_SHADER));
	create(scale);
	this->setTexture(TEXTURE, textureLoader.loadTexture(TEXTURE, TEXTURE_SIZE, TEXTURE_SIZE));
}

TexturedTetra::~TexturedTetra() {}

void TexturedTetra::create(float scale)
{
	glm::vec3 scalingVector(scale, scale, scale);

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));
	
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(VertexFormat),
		&vertices[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

	rotation = glm::vec3(10.0, 20.0, 30.0);
}

void TexturedTetra::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	// tell openGL which shaderProgram we are using
	glUseProgram(program);
	glBindVertexArray(vao);
	
	// set open gl to use this object's texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->getTexture(TEXTURE));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);
	
	// pass in shaderVariables
	glUniform3f(glGetUniformLocation(program, "rotation"), rotation.x, rotation.y, rotation.z);
	glUniform3f(glGetUniformLocation(program, "position"), position.x, position.y, position.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GLU_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	// draw using triangles
	glDrawArrays(GL_TRIANGLES, 0, 28);
}