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
void ModelsManager::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	//auto map iterator
	for (auto model : *this)
	{
		model->draw(projectionMatrix, viewMatrix);
	}
}

/**
*
*/
void ModelsManager::update()
{
	//auto map iterator
	for (auto model : *this)
	{
		model->update();
	}
}