#include "../Includes/SpriteRenderer.h";

SpriteRenderer::SpriteRenderer(GameObject* game_object, Material* material) :
	MonoBehaviour(game_object), m_material(material)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render(GLuint& vbo)
{
	RectTransform* transform = RectTransform::castToRect(m_game_object->getTransform());
	glm::vec2 position = transform->getPosition();
	glm::vec2 size = transform->getSize();

	getMaterial()->getShader()->setFloat("rotation", glm::radians(transform->getRotation()));

	float vertices[6][4] =
	{
		{ position.x,			position.y + size.y,	0.0f, 0.0f},
		{ position.x,			position.y,				0.0f, 1.0f},
		{ position.x + size.x,	position.y,				1.0f, 1.0f},
		{ position.x,			position.y + size.y,	0.0f, 0.0f},
		{ position.x + size.x,	position.y,				1.0f, 1.0f},
		{ position.x + size.x,	position.y + size.y,	1.0f, 0.0f}
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	getMaterial()->sendToShader();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	getMaterial()->unbindTextures();
}

Material* SpriteRenderer::getMaterial()
{
	return m_material;
}

void SpriteRenderer::setMaterial(Material* material)
{
	m_material = material;
}
