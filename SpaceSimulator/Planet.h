#include "TexturedSphere.h"
#include <string.h>

class Planet : public Rendering::TexturedSphere
{
public:
	Planet(float size, double mass, std::string textureFileName, int textureHeight, int textureWidth);
private:
};