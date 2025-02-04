in vec3 position_ws;
in vec2 texcoord_fs;
in vec3 normal_ws;

uniform int sample_base_texture = 0;
uniform int sample_emissive_texture = 0;

#exposed
uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D base_texture;
uniform int lit = 1;
uniform float gloss_power = 40.0;
uniform int use_emissive = 0;
uniform sampler2D emissive_texture;
uniform vec3 emissive_color = vec3(1.0, 1.0, 1.0);
uniform float emissive_intensity = 1.0;
#end_exposed

out vec4 fs_color;

void main()
{
	vec4 texture_sample = vec4(1.0, 1.0, 1.0, 1.0);
	if (sample_base_texture == 1)
		texture_sample = texture(base_texture, texcoord_fs);
	vec4 final_color = texture_sample * vec4(color, 1.0f);

	vec4 light = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specular_light = vec4(0.0, 0.0, 0.0, final_color.a);
	if (lit == 1)
	{
		float diffuse = max(dot(main_light.direction, normalize(normal_ws)), 0.0f);
		vec3 diffuse_light = main_light.color * diffuse;
		light = vec4(diffuse_light + main_light.ambient_color, 1.0);

		vec3 reflected_vector = normalize(reflect(-main_light.direction, normal_ws));
		vec3 eye_direction = normalize(main_camera.position - position_ws);
		float specular = max(dot(reflected_vector, eye_direction), 0.0f);
		specular = pow(specular, gloss_power);
		specular_light = vec4(main_light.color * specular, final_color.a);
	}

	vec4 emissive = vec4(0.0, 0.0, 0.0, 1.0);
	if (use_emissive == 1)
	{
		vec4 emissive_sample = vec4(1.0, 1.0, 1.0, 1.0);
		if (sample_emissive_texture == 1)
			emissive_sample = texture(emissive_texture, texcoord_fs);
		emissive = emissive_sample * vec4(emissive_color, 1.0) * emissive_intensity;
		emissive.a = final_color.a;
	}

	fs_color = vec4((final_color * light + specular_light + emissive).xyz, final_color.a);
}