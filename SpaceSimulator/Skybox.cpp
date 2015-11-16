#include "Skybox.h"
using namespace glm;

#define SKYBOX_SIZE 1990
#define SKYBOX_TEXTURE_FOLDER "darknebulaTextures/"
#define SKYBOX_TEXTURE_SIZE 1024

Skybox::Skybox() : TexturedSphere(SKYBOX_SIZE, SKYBOX_TEXTURE_FOLDER, SKYBOX_TEXTURE_SIZE){}
Skybox::Skybox(const std::string& texturesFolder, int textureSize) : TexturedSphere(SKYBOX_SIZE, texturesFolder, textureSize){}
