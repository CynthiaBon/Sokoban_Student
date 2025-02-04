#version 460

struct Camera
{
	vec3 position;
};

struct Light
{
	vec3 direction;
	vec3 color;
	vec3 ambient_color;
};

uniform Camera main_camera;
uniform Light main_light;