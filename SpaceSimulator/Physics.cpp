#include "Physics.h"

glm::vec3 Physics::calculateGravityVecor(const Planet& from, const Planet& to, float distance)
{
	// get a unit vector from one planet to the other
	glm::vec3 direction = getUnitVector(from.getPosition(), to.getPosition());
	// get the force of gravity between the two planets
	glm::vec3 gravityVector = direction * calculateGravityForce(from.getMass(), to.getMass(), distance);
	return gravityVector;
}

float Physics::calculateGravityForce(double mass1, double mass2, double distance)
{
	float force = (GRAVITY_CONSTANT*(mass1*mass2)) / (distance*distance);
	return force;
}

float Physics::calculateOrbitalVelocity(double mass1, double mass2, double distance)
{
	return sqrt((GRAVITY_CONSTANT*(mass1+mass2))/distance);
}

glm::vec3 Physics::getUnitVector(const glm::vec3& from, const glm::vec3& to)
{
	return glm::normalize(to - from);
}