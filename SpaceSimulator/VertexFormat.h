#pragma once
#include "glm\glm.hpp"

namespace Rendering
{

	struct VertexFormat
	{
		glm::vec3 position;//our first vertex attribute
		glm::vec4 color; // used to modify the color
		glm::vec2 texture;

		VertexFormat(const glm::vec3 &pos, const glm::vec4 &iColor)
		{
			position = pos;
			color = iColor;
			texture.x = 0;
			texture.y = 0;
		}

		VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iTexture)
		{
			position = iPos;
			texture = iTexture;
			color.r = 0; 
			color.g = 0;
			color.b = 0;
			color.a = 0;
		}

		VertexFormat(const glm::vec3 &iPos)
		{
			position = iPos;
			color.r = color.g = color.b = color.a = 0;
			texture.x = texture.y = 0;
		}

		VertexFormat(const VertexFormat& copy)
		{
			position = copy.position;
			texture = copy.texture;
			color = copy.color;
		}

		VertexFormat() {}
	};

}
