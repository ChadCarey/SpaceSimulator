#pragma once
#include <map>
#include <vector>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "VertexFormat.h"
#include <glm\glm.hpp>

namespace Rendering
{
	class Model
	{
	public:
		// CONSTRUCTORS
		Model();
		virtual ~Model();
		
		// GETTERS
		virtual GLuint getVao() const;
		virtual const std::vector<GLuint>& getVbos() const;
		virtual const GLuint getTexture(std::string textureName) const;

		// SETTERS
		virtual void setProgram(GLuint shaderName);
		virtual void setTexture(std::string textureName, GLuint texture);

		// METHODS
		virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		virtual void destroy();

	protected:
		std::map<std::string, GLuint> textures;
		GLuint vao;
		GLuint program;
		std::vector<GLuint> vbos;
		glm::vec3 position;
		glm::vec3 rotation;
	};
}
