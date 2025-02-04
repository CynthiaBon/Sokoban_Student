#version 460

layout (location = 0) in vec4 vertex;

#exposed
uniform float rotation;
#end_exposed

out vec2 texcoord_fs;

void main() {
	mat4 rotation_matrix;
	rotation_matrix[0] = vec4(cos(rotation), -sin(rotation), 0.0, 0.0);
	rotation_matrix[1] = vec4(sin(rotation), cos(rotation), 0.0, 0.0);
	rotation_matrix[2] = vec4(0.0, 0.0, 1.0, 0.0);
	rotation_matrix[3] = vec4(0.0, 0.0, 0.0, 1.0);

	texcoord_fs = vertex.zw;
	gl_Position = rotation_matrix * vec4(vertex.xy, 0.0, 1.0);
}