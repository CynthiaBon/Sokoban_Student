#include "../Includes/Skybox.h"

Skybox::Skybox()
{
	m_skybox = new GameObject("Skybox", false);
	Texture* texture = new Texture("Textures/Skybox.png", 0);
	m_skybox_shader = Shader::Find("Base Shader");
	m_skybox_material = new Material(m_skybox_shader, glm::vec3(1.0f), texture);
	m_skybox_material->setInt("lit", 0);
	m_skybox_material->setInt("use_emissive", 1);
	m_skybox_material->setTexture("emissive_texture", texture);
	m_skybox_material->setFloat("emissive_intensity", 1);
	m_skybox_renderer = new MeshRenderer(m_skybox, OBJLoader::loadObj("Meshes/Skybox.obj", false), m_skybox_material);
}

Skybox::~Skybox()
{
}

void Skybox::setTexture(Texture* texture)
{
	m_skybox_material->setBaseTexture(texture);
}

void Skybox::render(glm::vec3 camera_position)
{
	m_skybox->getTransform()->setPosition(camera_position);

	m_skybox_shader->use();
	glBindVertexArray(m_skybox_renderer->getMesh()->getBuffer());
	m_skybox_shader->setMatrix("matrices.model_matrix", m_skybox->getTransform()->getModelMatrix());
	m_skybox_renderer->render();
	glBindVertexArray(0);
	m_skybox_shader->unuse();
}
