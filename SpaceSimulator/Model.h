#pragma once
#include <map>
#include <vector>
#include <glm\glm.hpp>

namespace Rendering
{
	class Model
	{
	public:
		// CONSTRUCTORS
		Model(float scale);
		virtual ~Model();

		// GETTERS
		virtual GLuint GetVao() const;
		virtual const std::vector<GLuint>& GetVbos() const;
		virtual const GLuint GetTexture(std::string textureName) const;

		// SETTERS
		virtual void SetProgram(GLuint shaderName);
		virtual void SetTexture(std::string textureName, GLuint texture);

		// METHODS
		virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		virtual void Destroy();

	protected:
		std::map<std::string, GLuint> textures;
		GLuint vao;
		GLuint program;
		std::vector<GLuint> vbos;
		glm::vec3 position;
	};
}
