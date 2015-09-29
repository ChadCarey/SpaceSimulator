#pragma once
#include "TexturedSphere.h"
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
	Planet(long size, float mass, std::string textureFileName, int textureHeight, int textureWidth);
	~Planet();

	// getters
	float getMass() const;
	glm::vec3 getMovementVector();

	// setters
	inline void setMovementVector(glm::vec3& newVec) { setMovementVector(newVec.x, newVec.y, newVec.z); };
	void setMovementVector(float x, float y, float z);

	// methods
	void addNewOrbiter(Planet* p, float distance);
	void addVector(const glm::vec3& vector);
	void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
	void update() override;


private:
	// variables
	struct OrbiterInfo
	{
		Planet* planet;
		float distance;
	};
	std::vector<OrbiterInfo*> orbiters;
	glm::vec3 movementVector;
	float mass;
	
	/**
	* move will move the planet and all of it's orbiting planets by it's movementVector
	*/
	inline void move() { this->move(this->movementVector); };
	void move(glm::vec3& movement);
	void calculateOrbits();
};