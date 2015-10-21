#pragma once
#include "TexturedSphere.h"
#include <string.h>
#include <vector>
#include "PVector3.h"

/**
* Class Planet
* the planet class is a drawable TexturedSphere that also has a 
* tree-like structure that contains of of it's orbiting planets.
*/
class Planet : public Rendering::TexturedSphere
{
public:
	// constructors
	Planet(long size, long double mass, std::string textureFileName, int textureHeight, int textureWidth);
	~Planet();

	// getters
	long double getMass() const;
	PVector3 getMovementVector();
	PVector3 getPPosition() const;

	// setters
	inline void setMovementVector(PVector3& newVec) { setMovementVector(newVec.getX(), newVec.getY(), newVec.getZ()); };
	void setMovementVector(const long double& x, const long double& y, const long double& z);
	void setPPosition(const PVector3& newPos);
	void setPPosition(const long double& x, const long double& y, const long double& z);

	// methods
	void addNewOrbiter(Planet* p, const long double& distance);
	void addVector(const PVector3& vector);
	void addSystemVector(const PVector3& vector);
	void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
	void update() override;
	/**
	* move will move the planet and all of it's orbiting planets by it's movementVector
	*/
	void move();

	void applyGravity(Planet* p);
	void calculateOrbits();


private:
	// variables
	struct OrbiterInfo
	{
		Planet* planet;
		long double distance;
	};
	std::vector<OrbiterInfo*> orbiters;
	PVector3 movementVector;
	PVector3 precisePosition;
	long double mass;
	inline void syncVectors();
};