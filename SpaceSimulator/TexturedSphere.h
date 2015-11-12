#pragma once
#include "Model.h"
#include <stdarg.h>
#include <string.h>
#include "VertexFormat.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

/**
* draws a cube in the most inconvenient way possible: by creating the vertex array, triangle by triangle and passing it to the shader.
*/
namespace Rendering
{
		class TexturedSphere : public Model
		{
		public:
			TexturedSphere(float scale = 1);
            TexturedSphere(float scale, const std::string& textureFolder, int size);
			~TexturedSphere();

			void create(float scale = 1);
			virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
            void setCubeTexture(const std::string& texturesFolder, int textureSize);

		private:
            static std::vector<VertexFormat> unitVertices;
			void splitTriangle(VertexFormat& pointOne, VertexFormat& pointTwo, VertexFormat& pointThree, std::vector<VertexFormat>& output);
			void splitTetra(std::vector<VertexFormat>& vertices);
			void normalizeVertices(std::vector<VertexFormat>& vertices);
			void scale(std::vector<VertexFormat>& vertices, float& scale);
			int numVerticies;
			std::string currentTexture;
		};
}