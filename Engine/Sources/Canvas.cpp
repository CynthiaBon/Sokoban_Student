#include "../Includes/Canvas.h"

Canvas::Canvas()
{
	initializeBuffers();
}

Canvas::~Canvas()
{
}


void Canvas::initializeBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6.0f * 4.0f, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Canvas::draw(std::list<Shader*> m_shader_list)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBindVertexArray(m_vao);

	for (Shader* shader : m_shader_list)
	{
		if (!shader->isUi())
			continue;


		shader->use();

		for (GameObject* object : m_ui_elements)
		{
			SpriteRenderer* sprite = object->getComponent<SpriteRenderer>();
			if (sprite == nullptr)
				sprite = object->getComponent<TextRenderer>();
			if (sprite != nullptr && sprite->isActive()
				&& sprite->getMaterial()->getShader()->getName() == shader->getName())
			{
				sprite->render(m_vbo);
			}
		}

		shader->unuse();
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Canvas::addElement(GameObject* element)
{
	m_ui_elements.push_back(element);
}

void Canvas::removeElement(GameObject* element)
{
	m_ui_elements.remove(element);
}
