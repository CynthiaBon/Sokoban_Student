#pragma once

#include "SpriteRenderer.h"
#include "FontManager.h"

class GameEngine;

class TextRenderer : public SpriteRenderer
{
public:
	TextRenderer(GameObject* game_object, Material* material, std::string text = "");
	~TextRenderer();

	void render(GLuint& vbo) override;

	static glm::vec2 WindowAspect;

private:
	std::string m_text;
};