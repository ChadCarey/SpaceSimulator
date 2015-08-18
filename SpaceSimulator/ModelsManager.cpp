#include "ModelsManager.h"
using namespace Managers;

ModelsManager::ModelsManager()
{
	//by defaluts we are creating a triangle game object. Remove this later
	//Models::Triangle* triangle = new Models::Triangle();
	//triangle->SetProgram(ShaderManager::GetShader("colorShader"));
	//triangle->Create();
	//gameModelList["triangle"] = triangle;

	// square
	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;
}

ModelsManager::~ModelsManager()
{
	//auto -it's a map iterator (LOOK THIS UP AND UNDERSTAND IT (C++11))
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();

	for (auto model : gameModelListNDC)
	{
		delete model.second;
	}
	gameModelListNDC.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

void ModelsManager::DeleteModelNDC(const std::string& gameModelName)
{

	IGameObject* model = gameModelListNDC[gameModelName];
	model->Destroy();
	gameModelListNDC.erase(gameModelName);

}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

const IGameObject& ModelsManager::GetModelNDC(const std::string& gameModelName) const
{
	return (*gameModelListNDC.at(gameModelName));
}

void ModelsManager::Update()
{
		//auto -it's a map iterator (LOOK THIS UP AND UNDERSTAND IT (C++11))
		// for (auto model : gameModelList) // crashing here. not sure why
		for (model_map_it iter = gameModelList.begin(); iter != gameModelList.end(); ++iter)
		{
			// second is the second item in the row, namely a IGameObject*
			//model.second->Update();
			iter->second->Update();
		}
		for (auto model : gameModelListNDC)
		{
			model.second->Update();
		}
}

void ModelsManager::Draw()
{
	//auto -it's a map iterator (LOOK THIS UP AND UNDERSTAND IT (C++11))
	for (auto model : gameModelListNDC)
	{
		model.second->Draw();
	}
}

void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	CameraManager* camera = CameraManager::getInstance();
	glm::vec3 eyePosition(1, 4, 15.4);
	glm::vec3 target(0, 0, 0);
	glm::vec3 up(0, 1, 0);

	glm::mat4 m;

	m = camera->LookAt(eyePosition, target, up);
	//auto -it's a map iterator (LOOK THIS UP AND UNDERSTAND IT (C++11))
	for (auto model : gameModelList)
	{
		model.second->Draw(projection_matrix, m);// view_matrix);
	}
}

void ModelsManager::SetModel(const std::string& gameObjectName, IGameObject* gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}
