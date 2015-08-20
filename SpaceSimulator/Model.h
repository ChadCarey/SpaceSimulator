#pragma once
#include <map>
#include <vector>
#include "TextureLoader.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "VertexFormat.h"
#include "glm\glm.hpp"

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
		glm::vec3 getPosition();
		glm::vec3 getRotation();

		// SETTERS
		virtual void setProgram(GLuint shaderName);
		virtual void setTexture(std::string textureName, GLuint texture);
		void setPosition(const glm::vec3& newPosition);
		void setPosition(float x, float y, float z);
		void setRotation(const glm::vec3& newRotation);
		void setRotation(float x, float y, float z);

		// METHODS
		virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		virtual void update();
		void rotate(const glm::vec3& rotate);
		void rotate(float x, float y, float z);
		void move(const glm::vec3& dVector);
		void move(float x, float y, float z);

	protected:
		std::map<std::string, GLuint> textures;
		GLuint vao;
		GLuint program;
		std::vector<GLuint> vbos;
		glm::vec3 position;
		glm::vec3 rotation;

	private:
		virtual void destroy();
	};
}
