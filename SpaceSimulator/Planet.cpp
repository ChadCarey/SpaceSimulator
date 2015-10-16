#include "Planet.h"
#include "Physics.h"
using namespace glm;

Planet::Planet(long size, long double mass, std::string textureFileName, int textureHeight, int textureWidth) : TexturedSphere(size)
{
	this->setTexture(textureFileName, textureHeight, textureWidth);
	this->setMovementVector(0, 0, 0);
	this->mass = mass;
}

Planet::~Planet()
{
	for (auto orbiter : this->orbiters)
	{
		delete orbiter->planet;
		delete orbiter;
	}
}

void Planet::setMovementVector(const long double& x, const long double& y, const long double& z)
{
	this->movementVector.setX(x);
	this->movementVector.setY(y);
	this->movementVector.setZ(z);
}

void Planet::addNewOrbiter(Planet* p, const long double& distance)
{
	if (p != this)
	{
		p->setPPosition(this->precisePosition.getX() + distance, this->precisePosition.getY(), this->precisePosition.getZ());
		p->setMovementVector(0, 0, Physics::calculateOrbitalVelocity(p->getMass(), this->getMass(), distance));
		//p->setMovementVector(p->movementVector - Physics::calculateGravityVecor(*this, *p, distance)*2);

		// add it to the orbiter std::vector
		OrbiterInfo* orbiter = new OrbiterInfo();
		orbiter->planet = p;
		orbiter->distance = distance;
		this->orbiters.push_back(orbiter);
	}
}

void Planet::move(PVector3& movement)
{
	// move this planet by the given vector
	this->precisePosition.setX(this->precisePosition.getX() + movement.getX());
	this->precisePosition.setY(this->precisePosition.getY() + movement.getY());
	this->precisePosition.setZ(this->precisePosition.getZ() + movement.getZ());

	// move all orbiters by the given vector
	for (auto orbiter : this->orbiters)
	{
		// orbiting planets need to first be moved by their parent planet's vector 
		// Think relativity: moon orbits earth, which orbits sun
		orbiter->planet->move(movement);
		// then each child planet needs to be moved by it's own vertor
		orbiter->planet->move();
	}
}

void Planet::draw(const mat4& projection_matrix, const mat4& view_matrix)
{
	// the following will syncronize the high precision physics vectors
	// with the required drawing vectors (glm::vec3)
	this->syncVectors();
	// draw the planets using the superclasses draw method
	TexturedSphere::draw(projection_matrix, view_matrix);
	// then call draw for each of the orbiters so they can do the same
	for (auto orbiter : this->orbiters)
	{
		// draw the planet
		Planet* p = orbiter->planet;
		p->draw(projection_matrix, view_matrix);

		// draw a line from the parent planet to the orbiter
		/*glBegin(GL_LINES);
		glVertex3f(this->position.x, this->position.y, this->position.z);
		glVertex3f(p->position.x, p->position.y, p->position.z);
		glEnd();*/
	}
}

PVector3 Planet::getMovementVector()
{
	return this->movementVector;
}

void Planet::update()
{
	// calculate orbit correction vectors
	this->calculateOrbits();
	// move the planets
	this->move();
}

void Planet::calculateOrbits()
{
	// for each orbiter
	for (auto orbiter : this->orbiters)
	{
		// Calculate gravity vector and add it to the planet
		PVector3 gravityVector = Physics::calculateGravityVecor(*orbiter->planet, *this, orbiter->distance);
		orbiter->planet->addVector(gravityVector);
		// call calculateOrbits for each orbiter
		orbiter->planet->calculateOrbits();
	}
}

long double Planet::getMass() const
{
	return this->mass;
}

void Planet::addVector(const PVector3& vector)
{
	this->movementVector.setX(this->movementVector.getX() + vector.getX());
	this->movementVector.setY(this->movementVector.getY() + vector.getY());
	this->movementVector.setZ(this->movementVector.getZ() + vector.getZ());
}

PVector3 Planet::getPPosition() const
{
	return this->precisePosition;
}

/**
*
*
*/
void Planet::setPPosition(const PVector3& newPos)
{
	this->precisePosition.set(newPos);
}

/**
*
*
*/
void Planet::setPPosition(const long double& x, const long double& y, const long double& z)
{
	this->precisePosition.set(x, y, z);
}

/**
*
*
*/
void Planet::syncVectors()
{
	this->position.x = this->precisePosition.getX();
	this->position.y = this->precisePosition.getY();
	this->position.z = this->precisePosition.getZ();
}