#include "PVector3.h"
#include <limits>
#include <iostream>

const long double MAX_FLOAT = std::numeric_limits<float>::max();
const long double MIN_FLOAT = std::numeric_limits<float>::lowest();

PVector3::PVector3()
{
	this->set(0.0,0.0,0.0);
	//std::cout << "MAX_FLOAT: " << MAX_FLOAT << " MIN_FLOAT: " << MIN_FLOAT << std::endl;
}

/**
*
*
*/
PVector3::PVector3(const PVector3& origonal)
{
	this->set(origonal.getX(), origonal.getY(), origonal.getZ());
}

/**
*
*
*/
long double PVector3::getX() const
{
	return this->x;
}

/**
*
*
*/
long double PVector3::getY() const
{
	return this->y;
}

/**
*
*
*/
long double PVector3::getZ() const
{
	return this->z;
}

/**
*
*
*/
void PVector3::set(const long double& newX, const long double& newY, const long double& newZ)
{
	this->setX(newX);
	this->setY(newY);
	this->setZ(newZ);
}

/*
*
*/
void PVector3::set(const PVector3& newV)
{
	this->set(newV.getX(), newV.getY(), newV.getZ());
}

/**
*
*
*/
long double& PVector3::boundsFilter(const long double& newValue)
{
	long double returnValue = newValue;
	if (newValue > MAX_FLOAT)
		returnValue = MAX_FLOAT;
	else if (newValue < MIN_FLOAT)
		returnValue = MIN_FLOAT;
	if (returnValue != newValue)
		throw 20;
	return returnValue;
}

/**
*
*
*/
void PVector3::setX(const long double& newX)
{
	
	this->x = boundsFilter(newX);
	if (this->x != newX)
		std::cout << "newX was not within FLOAT bounds.\n";
}

/**
*
*
*/
void PVector3::setY(const long double& newY)
{
	this->y = boundsFilter(newY);
	if (this->y != newY)
		std::cout << "newY was not within FLOAT bounds.\n";
}

/**
*
*
*/
void PVector3::setZ(const long double& newZ)
{
	this->z = boundsFilter(newZ);
	if (this->z != newZ)
		std::cout << "newZ was not within FLOAT bounds.\n";
}

/**
*
*
*/
PVector3 PVector3::operator*(const long double& rhs) const
{
	PVector3 newVector;
	newVector.setX(this->getX() * rhs);
	newVector.setY(this->getY() * rhs);
	newVector.setZ(this->getZ() * rhs);
	return newVector;
}

/**
*
*
*/
PVector3 PVector3::operator/(const long double& rhs) const
{
	PVector3 newVector;
	newVector.setX(this->getX() / rhs);
	newVector.setY(this->getY() / rhs);
	newVector.setZ(this->getZ() / rhs);
	return newVector;
}

/**
*
*
*/
PVector3 PVector3::operator+(const PVector3& rhs) const
{
	PVector3 newVector;
	newVector.setX(this->getX() + rhs.getX());
	newVector.setY(this->getY() + rhs.getY());
	newVector.setZ(this->getZ() + rhs.getZ());
	return newVector;
}

/**
*
*
*/
PVector3 PVector3::operator-(const PVector3& rhs) const
{
	PVector3 newVector;
	newVector.setX(this->getX() - rhs.getX());
	newVector.setY(this->getY() - rhs.getY());
	newVector.setZ(this->getZ() - rhs.getZ());
	//std::cout << newVector.getX() << " " << newVector.getY() << " " << newVector.getZ() << std::endl;
	return newVector;
}

/**
*
*
*/
PVector3& PVector3::operator=(const PVector3& rhs)
{
	this->set(rhs.getX(), rhs.getY(), rhs.getZ());
	return *this;
}

/**
*
*
*/
long double PVector3::getLength() const
{
	long double sqx = this->getX();
	sqx = sqx * sqx;
	long double sqy = this->getY();
	sqy = sqy * sqy;
	long double sqz = this->getZ();
	sqz = sqz * sqz;
	return sqrtl(sqx + sqy + sqz);
}