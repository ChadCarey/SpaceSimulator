#pragma once
#include <map>
#include <vector>
#include "TextureLoader.h"
#include "ShaderManager.h"
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
		glm::vec3 getPosition() const;
		glm::vec3 getRotation();
		Managers::ShaderManager* getShaderManager();
		TextureLoader getTextureLoader();


		// SETTERS
		virtual void setProgram(GLuint shaderName);
		virtual void setTexture(std::string textureName, int height, int width);// GLuint texture);
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
		static TextureLoader textureLoader;
		static Managers::ShaderManager* shaderManager;

	private:
		virtual void destroy();
		static long long int modelCount;
	};
}
