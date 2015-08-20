#pragma once
#include "Model.h"
#include <stdarg.h>
#include "VertexFormat.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

/**
* draws a cube in the most inconvenient way possible: by creating the vertex array, triangle by triangle and passing it to the shader.
*/
namespace Rendering
{
		class TexturedCube : public Model
		{
		public:
			TexturedCube(float scale = 1);
			~TexturedCube();

			void create(float scale = 1);
			virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
		};
}