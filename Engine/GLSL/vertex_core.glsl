layout (location = 0) in vec3 position_os;
layout (location = 1) in vec2 texcoord_vs;
layout (location = 2) in vec3 normal_os;

out vec3 position_ws;
out vec2 texcoord_fs;
out vec3 normal_ws;

void main()
{
	position_ws = positionObjectToWorldSpace(vec4(position_os, 1.0f)).xyz;
	texcoord_fs = vec2(texcoord_vs.x, texcoord_vs.y * -1.0f);
	normal_ws = normalObjectToWorldSpace(normal_os);

	gl_Position = positionObjectToClipSpace(vec4(position_os, 1.0f));
}