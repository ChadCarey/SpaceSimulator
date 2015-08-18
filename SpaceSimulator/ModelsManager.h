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

		void Draw();
		void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		void Update();
		void DeleteModel(const std::string& gameModelName);
		const Model& GetModel(const std::string& gameModelName) const;
		void DeleteModelNDC(const std::string& gameModelName);
		const Model& GetModelNDC(const std::string& gameModelName) const;

		void SetModel(const std::string& gameObjectName, Model* gameObject);

	private:
		std::map<std::string, Model*> gameModelList; // This is not good practice because maps are not made for fast itterations, replace with a vector later once the engine is working
		std::map<std::string, Model*> gameModelListNDC;
	};
}
