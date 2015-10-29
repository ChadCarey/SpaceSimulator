#include "TexturedSphere.h"
#include <math.h>
using namespace Rendering;

#define VERTEX_SHADER "Sphere_Vertex_Shader.glsl"
#define FRAGMENT_SHADER "Sphere_Fragment_Shader.glsl"
#define TEXTURE "earth.bmp"
#define TRIANGLE_SPLITS 4
#define TEXTURE_WIDTH 300
#define TEXTURE_HEIGHT 150

TexturedSphere::TexturedSphere(float scale) : Model()
{
	this->setProgram(shaderManager->createProgram(VERTEX_SHADER, FRAGMENT_SHADER));
	create(scale);
	this->setTexture(TEXTURE, TEXTURE_HEIGHT, TEXTURE_WIDTH);
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
	glm::vec3 shiftVector(0.3333, 0.3333, 0.3333);


	// side 1
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) + shiftVector, glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) + shiftVector, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) + shiftVector, glm::vec2(0, 0)));
	
	// side 2
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) + shiftVector, glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) + shiftVector, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) + shiftVector, glm::vec2(1, 0)));

	// side 3
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0) + shiftVector, glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) + shiftVector, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) + shiftVector, glm::vec2(0, 0)));

	// side 1
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) + shiftVector, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) + shiftVector, glm::vec2(0, 0)));

	// side 2
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0) + shiftVector, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) + shiftVector, glm::vec2(1, 0)));

	// side 3
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0.5, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0) + shiftVector, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0) + shiftVector, glm::vec2(0, 0)));
	
	

	for (int i = 0; i < TRIANGLE_SPLITS; ++i)
	{
		splitTetra(vertices);
	}
	// normalize the verticies of the tetra to get a sphere
	normalizeVertices(vertices);
	// add a save sphere to texture method here later

	// scale the sphere
	this->scale(vertices, scale);

	numVerticies = vertices.size();


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

	rotation = glm::vec3(0.0, 0.0, 0.0);
}

void TexturedSphere::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

	// tell openGL which shaderProgram we are using
	glUseProgram(program);
	glBindVertexArray(vao);
	
	// set open gl to use this object's texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->getTexture(this->currentTexture));
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

void TexturedSphere::setTexture(std::string textureFileName, int height, int width)
{
	this->Model::setTexture(textureFileName, height, width);
	this->currentTexture = textureFileName;
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
	center.x = (pointTwo.position.x + pointThree.position.x) / 2.0;
	center.y = (pointTwo.position.y + pointThree.position.y) / 2.0;
	center.z = (pointTwo.position.z + pointThree.position.z) / 2.0;
	two.push_back(VertexFormat(center, pointThree.texture));
	three.push_back(VertexFormat(center, pointOne.texture));
	four.push_back(VertexFormat(center, pointTwo.texture));

	// split up the textures
	// triangle one
	one[0].texture.x = pointOne.texture.x;
	one[0].texture.y = pointOne.texture.y;
	one[1].texture.x = (pointOne.texture.x + pointTwo.texture.x) / 2.0;
	one[1].texture.y = (pointOne.texture.y + pointTwo.texture.y) / 2.0;
	one[2].texture.x = (pointOne.texture.x + pointThree.texture.x) / 2.0;
	one[2].texture.y = (pointOne.texture.y + pointThree.texture.y) / 2.0;

	// triangle two
	two[0].texture.x = pointTwo.texture.x;
	two[0].texture.y = pointTwo.texture.y;
	two[1].texture.x = one[1].texture.x;
	two[1].texture.y = one[1].texture.y;
	two[2].texture.x = (pointTwo.texture.x + pointThree.texture.x) / 2.0;
	two[2].texture.y = (pointTwo.texture.y + pointThree.texture.y) / 2.0;

	// triangle four
	four[0].texture.x = one[1].texture.x;
	four[0].texture.y = one[1].texture.y;
	four[1].texture.x = one[2].texture.x;
	four[1].texture.y = one[2].texture.y;
	four[2].texture.x = two[2].texture.x;
	four[2].texture.y = two[2].texture.y;

	// triangle three
	three[0].texture.x = pointThree.texture.x;
	three[0].texture.y = pointThree.texture.y;
	three[1].texture.x = four[1].texture.x;
	three[1].texture.y = four[1].texture.y;
	three[2].texture.x = four[2].texture.x;
	three[2].texture.y = four[2].texture.y;


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
	//normalizeVertices(output);
	for (int i = 0; i < output.size(); ++i)
	{
		vertices.push_back(output[i]);
	}
}


void TexturedSphere::normalizeVertices(std::vector<VertexFormat>& vertices)
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