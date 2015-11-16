#pragma once
#include "TexturedSphere.h"
#include <string.h>

/**
* Class Planet
* the planet class is a drawable TexturedSphere that also has a
* tree-like structure that contains of of it's orbiting planets.
*/
class Skybox : public Rendering::TexturedSphere
{
public:
    // constructors
    Skybox();
    Skybox(const std::string& texturesFolder, int textureSize);
};