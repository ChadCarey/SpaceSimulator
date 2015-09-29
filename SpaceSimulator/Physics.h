#pragma once
#include "Planet.h"

#define GRAVITY_CONSTANT 1.0

class Physics
{
public:
	static glm::vec3 calculateGravityVecor(const Planet& from, const Planet& to, float distance);
	static float calculateGravityForce(double mass1, double mass2, double distance);
	static float calculateOrbitalVelocity(double mass1, double mass2, double distance);
	static glm::vec3 getUnitVector(const glm::vec3& from, const glm::vec3& to);
};

