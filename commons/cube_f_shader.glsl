#version 330 core

out vec4 frag_color;
in vec3 position;
in vec3 normal;

uniform vec3 cam_pos;
uniform int indice;
uniform samplerCube skybox;

void main(void)
{
	float indice = 1.00;
	vec3 incident = normalize(position - cam_pos);
	if (indice == 2)
	{
	vec3 refracted = refract(incident, normalize(normal), 1.0);
	frag_color = vec4(mix(texture(skybox, refracted).rgb, vec3(1.0, 1.0, 1.0), 0.2), 1.0);
	}
	else
	{
		vec3 refracted = refract(incident, normalize(normal), 1.0 / 1.33);
	frag_color = vec4(mix(texture(skybox, refracted).rgb, vec3(0.0, 0.0, 1.0), 0.2), 1.0);
	}

}
