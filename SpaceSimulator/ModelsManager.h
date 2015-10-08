#pragma once
#include <list>
#include "ShaderManager.h"
#include "Model.h"
#include "CameraManager.h"
using namespace Rendering;

/**
* ModelsManager
* a specialized list that holds models and allows the user to update and draw the whole group
*/
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
