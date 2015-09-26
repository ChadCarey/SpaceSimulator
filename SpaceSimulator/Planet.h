#pragma once
#include "TexturedSphere.h"
#include "Vector3.h"
#include <string.h>
#include <vector>

/**
* Class Planet
* the planet class is a drawable TexturedSphere that also has a 
* tree-like structure that contains of of it's orbiting planets.
*/
class Planet : public Rendering::TexturedSphere
{
public:
	// constructors
	Planet(long size, long mass, std::string textureFileName, int textureHeight, int textureWidth);
	~Planet();

	// getters

	// setters

	// methods
	void addOrbiter(Planet* p, long distance);
	/**
	* move will move the planet and all of it's orbiting planets by it's movementVector
	*/
	inline void move() { this->move(this->movementVector); };

	void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;


private:
	// variables
	struct OrbiterInfo
	{
		Planet* planet;
		long distance;
	};
	std::vector<OrbiterInfo*> orbiters;
	SpacePhysics::Vector3 movementVector;
	long mass;
	
	// methods
	void move(SpacePhysics::Vector3& movement);
};