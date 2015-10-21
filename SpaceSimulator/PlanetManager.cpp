#include "PlanetManager.h"

void PlanetManager::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto p : *this)
	{
		p->draw(projection_matrix, view_matrix);
	}
}

void PlanetManager::update()
{
	for (std::list<Planet*>::iterator p = this->begin(); p != this->end(); ++p)
	{
		// calculate each orbital system's orbit vectors
		(*p)->calculateOrbits();
		// here we will update each planetary system with respect to each other (gravity)
		for (std::list<Planet*>::iterator p2 = p; p2 != this->end(); ++p2)
		{
			(*p)->applyGravity(*p2);
		}
		// now move each system
		(*p)->move();
	}
}

/* 
* this function is intended to run on a separate thread and check for planets entering and exiting orbits
* when a free moving object is found to be orbiting another object, it will then remove that object from the
* list of planet* and add it as a child of the orbited object
*/
void PlanetManager::OrbitChecker()
{

}