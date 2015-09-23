#include "Planet.h"

Planet::Planet(float size, double mass, std::string textureFileName, int textureHeight, int textureWidth) : TexturedSphere(size)
{
	this->setTexture(textureFileName, textureHeight, textureWidth);
}