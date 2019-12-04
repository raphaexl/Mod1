#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out	vec2	uvs;
out	vec3	position;
out	vec3	c_color;

void main()
{
	c_color = aPos;
	uvs = aTexcoord;

//	normal = mat3(transpose(inverse(model))) * aNormal;
	position = vec3(model * vec4(aPos.xyz, 1.0));
	gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
}
