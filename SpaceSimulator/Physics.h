#pragma once
#include "Planet.h"

#define GRAVITY_CONSTANT 1.0

class Physics
{
public:
	static PVector3 calculateGravityVecor(const Planet& from, const Planet& to, const long double& distance);
	static long double calculateGravityForce(long double mass1, long double mass2, long double distance);
	static long double calculateOrbitalVelocity(long double mass1, long double mass2, long double distance);
	static PVector3 getUnitVector(const PVector3& from, const PVector3& to);
};

