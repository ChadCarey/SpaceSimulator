#include "TexturedSphere.h"
using namespace Rendering;

#define VERTEX_SHADER "Texture_Vertex_Shader.glsl"
#define FRAGMENT_SHADER "Texture_Fragment_Shader.glsl"
#define TEXTURE "Neptune.bmp"
#define TRIANGLE_SPLITS 5
#define TEXTURE_WIDTH 300
#define TEXTURE_HEIGHT 150

TexturedSphere::TexturedSphere(float scale)
{
	this->setProgram(shaderManager->createProgram(VERTEX_SHADER, FRAGMENT_SHADER));
	create(scale);
	this->setTexture(TEXTURE, textureLoader.loadTexture(TEXTURE, TEXTURE_WIDTH, TEXTURE_HEIGHT));
}

TexturedSphere::~TexturedSphere() {}

void TexturedSphere::create(float scale)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	// Build tetrahedron

	// side 1
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));
	
	// side 2
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0, 1)));

	// side 3
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0, 1)));

	// side 4
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0, 1)));

	for (int i = 0; i < TRIANGLE_SPLITS; ++i)
	{
		splitTetra(vertices);
	}
	normalize(vertices);
	this->scale(vertices, scale);

	numVerticies = vertices.size();


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

void TexturedSphere::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
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
	glDrawArrays(GL_TRIANGLES, 0, numVerticies);
}

void TexturedSphere::splitTriangle(VertexFormat& pointOne, VertexFormat& pointTwo, VertexFormat& pointThree, std::vector<VertexFormat>& output)
{
	// this one triangle will be split into 4 triangles
	std::vector<VertexFormat> one;
	one.push_back(pointOne);
	std::vector<VertexFormat> two;
	two.push_back(pointTwo);
	std::vector<VertexFormat> three;
	three.push_back(pointThree);
	std::vector<VertexFormat> four; // starts empty

	glm::vec3 center;
	// get the center vectors and add them to the vectors that use them

	// first center glm::vec3
	center.x = (pointOne.position.x + pointTwo.position.x) / 2;
	center.y = (pointOne.position.y + pointTwo.position.y) / 2;
	center.z = (pointOne.position.z + pointTwo.position.z) / 2;
	one.push_back(VertexFormat(center, pointTwo.texture));
	two.push_back(VertexFormat(center, pointOne.texture));
	four.push_back(VertexFormat(center, pointThree.texture));

	// second center glm::vec3
	center.x = (pointOne.position.x + pointThree.position.x) / 2;
	center.y = (pointOne.position.y + pointThree.position.y) / 2;
	center.z = (pointOne.position.z + pointThree.position.z) / 2;
	one.push_back(VertexFormat(center, pointThree.texture));
	three.push_back(VertexFormat(center, pointTwo.texture));
	four.push_back(VertexFormat(center, pointOne.texture));

	// third center glm::vec3
	center.x = (pointTwo.position.x + pointThree.position.x) / 2;
	center.y = (pointTwo.position.y + pointThree.position.y) / 2;
	center.z = (pointTwo.position.z + pointThree.position.z) / 2;
	two.push_back(VertexFormat(center, pointThree.texture));
	three.push_back(VertexFormat(center, pointOne.texture));
	four.push_back(VertexFormat(center, pointTwo.texture));

	// add them all to the output std::vector
	for (int i = 0; i < one.size(); ++i)
	{
		output.push_back(one[i]);
	}

	for (int i = 0; i < two.size(); ++i)
	{
		output.push_back(two[i]);
	}
	
	for (int i = 0; i < three.size(); ++i)
	{
		output.push_back(three[i]);
	}
	
	for (int i = 0; i < four.size(); ++i)
	{
		output.push_back(four[i]);
	}
}

void TexturedSphere::splitTetra(std::vector<VertexFormat>& vertices)
{
	int size = vertices.size();
	std::vector<VertexFormat> output;
	for (int i = 0; i < size; i+=3)
	{
		splitTriangle(vertices[i], vertices[i + 1], vertices[i + 2], output);
	}
	vertices.clear();
	normalize(output);
	for (int i = 0; i < output.size(); ++i)
	{
		vertices.push_back(output[i]);
	}
}


void TexturedSphere::normalize(std::vector<VertexFormat>& vertices)
{
	for (std::vector<VertexFormat>::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		it->position = glm::normalize(it->position);
	}
}


void TexturedSphere::scale(std::vector<VertexFormat>& vertices, float& scale)
{
	glm::vec3 scalingVector(scale, scale, scale);
	for (std::vector<VertexFormat>::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		it->position *= scalingVector;
	}
}