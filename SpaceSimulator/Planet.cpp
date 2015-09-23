#include "Planet.h"

Planet::Planet(long size, long mass, std::string textureFileName, int textureHeight, int textureWidth) : TexturedSphere(size)
{
	this->setTexture(textureFileName, textureHeight, textureWidth);
	this->movementVector.set(0, 0, 0);
}

Planet::~Planet()
{
	for (auto orbiter : this->orbiters)
	{
		delete orbiter->planet;
		delete orbiter;
	}
}

void Planet::addOrbiter(Planet* p, long distance)
{
	// calculate correct orbiter vector in the direction of the current planet's vector
		// if the is no current vector we give it a random direction
	// add it to the orbiter std::vector
	OrbiterInfo* orbiter = new OrbiterInfo();
	orbiter->planet = p;
	orbiter->distance = distance;
	this->orbiters.push_back(orbiter);
}

void Planet::move(SpacePhysics::Vector3& movement)
{
	// move this planet by the given vector
	this->position.x += movement.x;
	this->position.y += movement.y;
	this->position.z += movement.z;

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

void Planet::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	// draw the planets using the superclasses draw method
	TexturedSphere::draw(projection_matrix, view_matrix);
	// then call draw for each of the orbiters so they can do the same
	for (auto orbiter : this->orbiters)
	{
		orbiter->planet->draw(projection_matrix, view_matrix);
	}
}