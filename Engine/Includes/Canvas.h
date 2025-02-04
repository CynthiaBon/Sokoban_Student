#pragma once

#include "RectTransform.h"
#include "TextRenderer.h"
#include "GameObject.h"

class Canvas
{
public:
	Canvas();
	~Canvas();

	void draw(std::list<Shader*> shader_list);

	void addElement(GameObject* element);
	void removeElement(GameObject* element);

private:
	void initializeBuffers();

private:
	std::list<GameObject*> m_ui_elements;

	glm::mat4 m_projection_matrix;

	GLuint m_vao;
	GLuint m_vbo;
};