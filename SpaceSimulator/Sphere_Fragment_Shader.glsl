#version 420 core

in vec3 textureDir; // Direction vector representing a 3D texture coordinate
uniform samplerCube cubemap;  // Cubemap texture sampler

layout(location = 0) out vec4 color;

void main()
{             
    color = texture(cubemap, textureDir);
}  
