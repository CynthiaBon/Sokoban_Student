#version 460

struct Matrices
{
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 projection_matrix;
};

uniform Matrices matrices;

vec4 positionObjectToClipSpace(vec4 objectSpacePosition)
{
	return matrices.projection_matrix * matrices.view_matrix * matrices.model_matrix * objectSpacePosition;
}

vec4 positionObjectToWorldSpace(vec4 objectSpacePosition)
{
	return matrices.model_matrix * objectSpacePosition;
}

vec3 normalObjectToWorldSpace(vec3 objectSpaceNormal)
{
	return mat3(matrices.model_matrix) * objectSpaceNormal;
}