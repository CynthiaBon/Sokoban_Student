#include "../Includes/TextRenderer.h"

glm::vec2 TextRenderer::WindowAspect = glm::vec2(1.0f);

TextRenderer::TextRenderer(GameObject* game_object, Material* material, std::string text) :
	SpriteRenderer(game_object, material), m_text(text)
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(GLuint& vbo)
{
	RectTransform* transform = RectTransform::castToRect(m_game_object->getTransform());
	glm::vec2 position = transform->getPosition();
	glm::vec2 size = transform->getSize();

	getMaterial()->getShader()->setFloat("rotation", glm::radians(transform->getRotation()));

	std::string::const_iterator c;
	float x = position.x;
	for (c = m_text.begin(); c != m_text.end(); c++)
	{
		Character character = FontManager::getInstance()->getCharacter(*c);

		float x_pos = x + character.Bearing.x * size.x * WindowAspect.x;
		float y_pos = position.y - (character.Size.y - character.Bearing.y) * size.y * WindowAspect.y;

		float width = character.Size.x * size.x * WindowAspect.x;
		float height = character.Size.y * size.y * WindowAspect.y;

		float vertices[6][4] =
		{
			{ x_pos,			y_pos + height,		0.0f, 0.0f},
			{ x_pos,			y_pos,				0.0f, 1.0f},
			{ x_pos + width,	y_pos,				1.0f, 1.0f},
			{ x_pos,			y_pos + height,		0.0f, 0.0f},
			{ x_pos + width,	y_pos,				1.0f, 1.0f},
			{ x_pos + width,	y_pos + height,		1.0f, 0.0f}
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		getMaterial()->setBaseTexture(character.CharTexture);
		getMaterial()->sendToShader();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (character.Advance >> 6) * size.x * WindowAspect.x;
	}

	getMaterial()->unbindTextures();
}
