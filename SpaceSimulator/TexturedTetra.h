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
		class TexturedTetra : public Model
		{
		public:
			TexturedTetra(float scale = 1);
			~TexturedTetra();

			void create(float scale = 1);
			virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
		};
}