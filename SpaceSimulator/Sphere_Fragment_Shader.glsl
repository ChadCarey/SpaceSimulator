#version 420 core

layout(location = 0) out vec4 out_color;
uniform samplerCube Texture0;
in vec3 texcoord;

void main(void)
{
	out_color = texture(Texture0, texcoord);
}