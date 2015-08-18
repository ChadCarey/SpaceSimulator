#pragma once
#include "Model.h"
#include<time.h>
#include<stdarg.h>
#include "VertexFormat.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

/**
* draws a cube in the most inconvenient way possible: by creating the vertex array, triangle by triangle and passing it to the shader.
*/

namespace Models
{
	
	class CubeTexture : public Models::Model
	{
	public:
		CubeTexture();
		~CubeTexture();

		void Create(float scale = 1);
		virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
		virtual void Update() override final;

	private:
		glm::vec3 rotation, rotation_speed, rotation_sin;
	};
}