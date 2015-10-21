#pragma once
#include "Planet.h"
#include <list>

/**
* This class manages interactions between planets and planetary objects
*/
class PlanetManager : public std::list<Planet*>
{
public:
	PlanetManager() : std::list<Planet*>() { /* start OrbitChecker on back thread */ };
	void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
	void update();
	
private:

	/* this function is intended to run on a separate thread and check for planets entering and exiting orbits*/
	static void OrbitChecker();
};