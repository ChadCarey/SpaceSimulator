#version 420 core
 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
 
uniform mat4 projection_matrix, view_matrix;
uniform vec3 rotation;
uniform vec3 position;
 
out vec2 texcoord;

void main()
{
	vec3 final_position = in_position + position;

    texcoord = in_texture;
    mat4 rotate_x, rotate_y, rotate_z;
     
    rotate_x = mat4(1.0, 0.0, 0.0, 0.0, 0.0, cos(rotation.x), sin(rotation.x), 0.0, 0.0, -sin(rotation.x), cos(rotation.x), 0.0, 0.0, 0.0, 0.0, 1.0);
    rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0, 0.0, 1.0, 0.0, 0.0, sin(rotation.y), 0.0, cos(rotation.y), 0.0, 0.0, 0.0, 0.0, 1.0);
    rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0, sin(rotation.z), cos(rotation.z), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
 
    gl_Position = projection_matrix * view_matrix * rotate_y * rotate_x * rotate_z * vec4(final_position, 1);

}