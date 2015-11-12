#include "TexturedSphere.h"
#include <math.h>
using namespace Rendering;

#define VERTEX_SHADER "Sphere_Vertex_Shader.glsl"
#define FRAGMENT_SHADER "Sphere_Fragment_Shader.glsl"
#define TEXTURE_FOLDER "earthTextures/"
#define TRIANGLE_SPLITS 3
#define TEXTURE_SIZE 80

TexturedSphere::TexturedSphere(float scale) : Model()
{
	this->setProgram(shaderManager->createProgram(VERTEX_SHADER, FRAGMENT_SHADER));
	create(scale);
	this->setCubeTexture(TEXTURE_FOLDER, TEXTURE_SIZE);
}

TexturedSphere::TexturedSphere(float scale, const std::string& textureFolder, int size) : Model()
{
    this->setProgram(shaderManager->createProgram(VERTEX_SHADER, FRAGMENT_SHADER));
    create(scale);
    this->setCubeTexture(textureFolder, size);
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

	// Build a cube

	// front
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, 10.0)));

	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, 10.0)));

	// right
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, -10.0)));

	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, 10.0)));

	// back
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, -10.0)));

	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, -10.0)));

	// left
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, 10.0)));

	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, -10.0)));

	// upper
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, -10.0)));

	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, 10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, 10.0, -10.0)));

	// bottom
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, 10.0)));

	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, -10.0)));
	vertices.push_back(VertexFormat(glm::vec3(-10.0, -10.0, 10.0)));
	vertices.push_back(VertexFormat(glm::vec3(10.0, -10.0, 10.0)));



	for (int i = 0; i < TRIANGLE_SPLITS; ++i)
	{
		splitTetra(vertices);
	}
	// normalize the verticies of the tetra to get a sphere
	normalizeVertices(vertices);


	// scale the sphere
	this->scale(vertices, scale);

	numVerticies = vertices.size();


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

	rotation = glm::vec3(0.0, 0.0, 0.0);
}

void TexturedSphere::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

	// tell openGL which shaderProgram we are using
    
	glUseProgram(program);
    
	
	// pass in shaderVariables
	glUniform3f(glGetUniformLocation(program, "position"), position.x, position.y, position.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GLU_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, &projection_matrix[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->getTexture(this->currentTexture));
    glDrawArrays(GL_TRIANGLES, 0, this->numVerticies);
    
}

void TexturedSphere::setCubeTexture(const std::string& texturesFolder, int size)
{
    GLuint texture = this->getTexture(texturesFolder);
    // if the texture == 0 then it is not found, create it
    if (texture == 0)
    {
        texture = this->textureLoader.loadCubemapTexture(texturesFolder, size);
        if (texture != 0)
        {
            textures[texturesFolder] = texture;
        }
    }
    this->currentTexture = texturesFolder;
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