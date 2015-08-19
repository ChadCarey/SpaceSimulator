#pragma once
#include <map>
#include "ShaderManager.h"
#include "Model.h"
#include "CameraManager.h"
using namespace Rendering;

typedef std::map<std::string, Model*>::iterator model_map_it;

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager();
		~ModelsManager();

		void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		void deleteModel(const std::string& gameModelName);
		const Model& getModel(const std::string& gameModelName) const;
		void deleteModelNDC(const std::string& gameModelName);
		const Model& getModelNDC(const std::string& gameModelName) const;

		void setModel(const std::string& gameObjectName, Model* gameObject);

	private:
		std::map<std::string, Model*> gameModelList; // This is not good practice because maps are not made for fast itterations, replace with a vector later once the engine is working
		std::map<std::string, Model*> gameModelListNDC;
	};
}
