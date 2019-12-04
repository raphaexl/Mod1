#version 330 core

out vec4 frag_color;
in vec3 position;
in vec3 c_color;
in vec2 uvs;
//in vec3 normal;

uniform vec3 cam_pos;
uniform sampler2D t_texture;

void main(void)
{
	frag_color = vec4(mix(texture(t_texture, uvs).rgb, vec3(1.0, 1.0, 1.0) ,mix(0, 0.04, c_color.y)), 1.0);
}
