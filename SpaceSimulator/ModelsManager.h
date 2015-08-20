#pragma once
#include <list>
#include "ShaderManager.h"
#include "Model.h"
#include "CameraManager.h"
using namespace Rendering;


namespace Managers
{
	class ModelsManager : public std::list<Model*>
	{
	public:
		ModelsManager();

		void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		virtual void update();
	};
}
