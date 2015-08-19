#include "ModelsManager.h"
using namespace Managers;

/**
*
*
*/
ModelsManager::ModelsManager() {}

/**
*
*
*/
ModelsManager::~ModelsManager()
{
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

/**
*
*
*/
void ModelsManager::deleteModel(const std::string& gameModelName)
{
	Model* model = gameModelList[gameModelName];
	model->destroy();
	gameModelList.erase(gameModelName);
}

/**
*
*
*/
const Model& ModelsManager::getModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

/**
*
*
*/
void ModelsManager::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	//auto map iterator
	for (auto model : gameModelList)
	{
		model.second->draw(projectionMatrix, viewMatrix);
	}
}

/**
*
*
*/
void ModelsManager::addModel(const std::string& gameObjectName, Model* gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}
