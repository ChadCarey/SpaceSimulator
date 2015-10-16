#include "Physics.h"

PVector3 Physics::calculateGravityVecor(const Planet& from, const Planet& to, const long double& distance)
{
	// get a unit vector from one planet to the other
	PVector3 direction = getUnitVector(from.getPPosition(), to.getPPosition());
	// get the force of gravity between the two planets
	PVector3 gravityVector = direction * calculateGravityForce(from.getMass(), to.getMass(), distance);
	return gravityVector;
}

long double Physics::calculateGravityForce(long double mass1, long double mass2, long double distance)
{
	long double force = (GRAVITY_CONSTANT*(/*mass1*/mass2)) / (distance*distance);
	return force;
}

long double Physics::calculateOrbitalVelocity(long double mass1, long double mass2, long double distance)
{
	return sqrt((GRAVITY_CONSTANT*(mass1+mass2))/distance);
}

PVector3 Physics::getUnitVector(const PVector3& from, const PVector3& to)
{
	PVector3 dVec = to - from;
	long double length = dVec.getLength();
	return dVec/length;
}