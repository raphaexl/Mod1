#version 330 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
out	vec3 texcoords;

void main()
{
	texcoords = a_Pos;
	gl_Position = P * V * M * vec4(a_Pos, 1.0);
}
