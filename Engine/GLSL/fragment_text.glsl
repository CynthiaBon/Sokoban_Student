#version 460

in vec2 texcoord_fs;

#exposed
uniform sampler2D base_texture;
uniform vec3 color = vec3(1.0, 1.0, 1.0);
#end_exposed

out vec4 fs_color;

void main()
{
	vec4 char_sampled = vec4(1.0, 1.0, 1.0, texture(base_texture, texcoord_fs).x);
	fs_color = char_sampled * vec4(color, 1.0f);
}