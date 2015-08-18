#pragma once
#include "Model.h"
#include<time.h>
#include<stdarg.h>
#include "VertexFormat.h"

/**
* draws a IndexedCube in the most inconvenient way possible: by creating the vertex array, triangle by triangle and passing it to the shader.
*/

namespace Models
{
	class IndexedCube : public Models::Model
	{
	public:
		IndexedCube();
		~IndexedCube();

		void Create();
		virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
		virtual void Update() override final;

	private:
		glm::vec3 rotation, rotation_speed;
	};
}