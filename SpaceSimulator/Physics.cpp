#include "Physics.h"

PVector3 Physics::calculateGravityVecor(const Planet& from, const Planet& to, const long double& distance)
{
	// get a unit vector from one planet to the other
	PVector3 direction = getUnitVector(from.getPPosition(), to.getPPosition());
	// get the acceleration of gravity between the two planets 
	// A = F/M, this equates to the mass of the first planet cancling out to 1.0 in the force equation
	long double acMag = calculateGravityForce(/*from.getMass() / from.getMass() =*/ 1.0, to.getMass(), distance);
	direction *= acMag;
	return direction;
}

long double Physics::calculateGravityForce(long double mass1, long double mass2, long double distance)
{
	long double force = (GRAVITY_CONSTANT*(mass1*mass2)) / (distance*distance);
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

long double Physics::calculateDistance(const PVector3& one, const PVector3& two)
{
	long double dx = one.getX() - two.getX();
	long double dy = one.getY() - two.getY();
	long double dz = one.getZ() - two.getZ();
	return sqrtl(dx*dx + dy*dy + dz*dz);
}