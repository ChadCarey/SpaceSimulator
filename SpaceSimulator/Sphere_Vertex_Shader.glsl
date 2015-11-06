#version 420 core

layout(location = 0) in vec3 in_position;
uniform mat3 position;
uniform mat4 projection;
uniform mat4 view;

out vec3 textureDir;

void main()
{
    vec3 final_position;
    final_position.x = in_position.x + position.x;
    final_position.y = in_position.y + position.y;
    final_position.z = in_position.z + position.z;

    gl_Position = projection * view * vec4(final_position, 1.0);

    textureDir = in_position;
}  

