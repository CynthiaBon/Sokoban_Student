#include "../Includes/Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
	m_vertices(vertices), m_indices(indices)
{
	createObjectsBuffer();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_objects_buffer);
	glDeleteBuffers(1, &m_vertices_buffer);
	glDeleteBuffers(1, &m_indices_buffer);
}

GLint Mesh::getVerticesCount()
{
	return m_vertices.size();
}

GLint Mesh::getIndicesCount()
{
	return m_indices.size();
}

void Mesh::createObjectsBuffer()
{
	glCreateVertexArrays(1, &m_objects_buffer);
	glBindVertexArray(m_objects_buffer);

	glGenBuffers(1, &m_vertices_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertices_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

GLuint Mesh::getBuffer()
{
	return m_objects_buffer;
}
