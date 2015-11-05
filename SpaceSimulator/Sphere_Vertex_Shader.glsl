#version 420 core

layout(location = 0) in vec3 in_position;
uniform mat3 position;
uniform mat4 projection;
uniform mat4 view;

out vec3 textureDir;

void main()
{
    //vec3 final_position = in_position + position;

    gl_Position = projection * view * vec4(in_position, 1.0);

    textureDir = in_position;
}  

