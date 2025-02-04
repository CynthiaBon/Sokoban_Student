#version 460

in vec2 texcoord_fs;

uniform int sample_base_texture = 0;

#exposed
uniform sampler2D base_texture;
uniform vec3 color = vec3(1.0, 1.0, 1.0);
#end_exposed

out vec4 fs_color;

void main()
{
	vec4 sampled_texture = vec4(1.0, 1.0, 1.0, 1.0);
	if (sample_base_texture == 1)
		sampled_texture = texture(base_texture, texcoord_fs);
	fs_color = sampled_texture * vec4(color, 1.0f);
}