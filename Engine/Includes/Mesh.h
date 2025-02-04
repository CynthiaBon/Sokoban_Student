#pragma once

#include "Shader.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	~Mesh();

	GLint getVerticesCount();
	GLint getIndicesCount();
	GLuint getBuffer();

private:
	void createObjectsBuffer();

private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;

	GLuint m_objects_buffer;
	GLuint m_vertices_buffer;
	GLuint m_indices_buffer;
};
