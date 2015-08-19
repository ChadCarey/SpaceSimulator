#include "TexturedCube.h"
using namespace Rendering;

#define PI 3.14159265

TexturedCube::TexturedCube(float scale)
{
	create(scale);
}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::create(float scale)
{
	glm::vec3 scalingVector(scale, scale, scale);

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	std::vector<VertexFormat> vertices;

	// THE FOLLOWING WILL BE REPLACED BY A VERTICESLOADER METHOD IN MODEL CLASS

	std::vector<unsigned int>  indices = { 0, 1, 2, 0, 2, 3,   //front
		4, 5, 6, 4, 6, 7,   //right
		8, 9, 10, 8, 10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23 }; //bottom

	//front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(0, 1)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(0, 1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0) * scalingVector,
		glm::vec2(0, 1)));

	////bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) * scalingVector,
		glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) * scalingVector,
		glm::vec2(0, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(VertexFormat),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	rotation = glm::vec3(45.0, 45.0, 45.0);
}

void TexturedCube::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	// tell openGL which shaderProgram we are using
	glUseProgram(program);
	glBindVertexArray(vao);
	
	// pass in shaderVariables
	glUniform3f(glGetUniformLocation(program, "rotation"), rotation.x, rotation.y, rotation.z);
	glUniform3f(glGetUniformLocation(program, "position"), 0, 0, 0);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GLU_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	// draw using triangles
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}