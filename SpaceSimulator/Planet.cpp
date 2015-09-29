#include "Planet.h"
#include "Physics.h"
using namespace glm;

Planet::Planet(long size, float mass, std::string textureFileName, int textureHeight, int textureWidth) : TexturedSphere(size)
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

void Planet::setMovementVector(float x, float y, float z)
{
	this->movementVector.x = x;
	this->movementVector.y = y;
	this->movementVector.z = z;
}

void Planet::addNewOrbiter(Planet* p, float distance)
{
	if (p != this)
	{
		p->setPosition(this->position.x + distance, this->position.y, this->position.z);
		p->setMovementVector(0, 0, Physics::calculateOrbitalVelocity(p->getMass(), this->getMass(), distance));

		// add it to the orbiter std::vector
		OrbiterInfo* orbiter = new OrbiterInfo();
		orbiter->planet = p;
		orbiter->distance = distance;
		this->orbiters.push_back(orbiter);
	}
}

void Planet::move(vec3& movement)
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

		// calculate a corection vector and add it to the planets current vector
		// NOTE: this is a tempory hack
		glm::vec3 correctPos = (Physics::getUnitVector(this->getPosition(), orbiter->planet->getPosition()) * orbiter->distance) + this->getPosition();
		glm::vec3 correctionVector = correctPos - orbiter->planet->getPosition();
		orbiter->planet->addVector(correctionVector);

	}
}

void Planet::draw(const mat4& projection_matrix, const mat4& view_matrix)
{
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

vec3 Planet::getMovementVector()
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
		vec3 gravityVector = Physics::calculateGravityVecor(*orbiter->planet, *this, orbiter->distance);
		orbiter->planet->addVector(gravityVector);
		// call calculateOrbits for each orbiter
		orbiter->planet->calculateOrbits();
	}
}

float Planet::getMass() const
{
	return this->mass;
}

void Planet::addVector(const glm::vec3& vector)
{
	this->movementVector.x += vector.x;
	this->movementVector.y += vector.y;
	this->movementVector.z += vector.z;
}