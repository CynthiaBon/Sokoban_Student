#version 460

layout (location = 0) in vec2 position_vs;
layout (location = 1) in vec2 texcoord_vs;

out vec2 texcoord_fs;

void main() {
	texcoord_fs = texcoord_vs;
	gl_Position = vec4(position_vs, 0.0, 1.0);
}