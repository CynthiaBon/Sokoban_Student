#include "../Includes/MeshRenderer.h"

MeshRenderer::MeshRenderer(GameObject* game_object, Mesh* mesh, Material* material) :
	MonoBehaviour(game_object), m_mesh(mesh), m_material(material)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render()
{
	glBindVertexArray(getMesh()->getBuffer());
	m_material->sendToShader();

	GLint indicesCount = m_mesh->getIndicesCount();
	if (indicesCount > 0)
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVerticesCount());

	m_material->unbindTextures();
}

Mesh* MeshRenderer::getMesh()
{
	return m_mesh;
}

void MeshRenderer::setMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

Material* MeshRenderer::getMaterial()
{
	return m_material;
}

void MeshRenderer::setMaterial(Material* material)
{
	m_material = material;
}
