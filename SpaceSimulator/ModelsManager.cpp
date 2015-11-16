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
	for (auto model : *this)
	{
		model->update();
	}
}