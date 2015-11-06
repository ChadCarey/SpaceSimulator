#version 420 core

in vec3 textureDir; // Direction vector representing a 3D texture coordinate
uniform samplerCube cubemap;  // Cubemap texture sampler

layout(location = 0) out vec4 color;

void main()
{
    // the textures are mirrored and flipped so we will need to undo this
    vec3 final_dir;
    final_dir.x = -textureDir.x;
    final_dir.y = -textureDir.y;
    final_dir.z = textureDir.z;
    color = texture(cubemap, final_dir);
}  
