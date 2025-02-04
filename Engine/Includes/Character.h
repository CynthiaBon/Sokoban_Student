#pragma once

#include "libs.h"
#include "Texture.h"

struct Character
{
	Texture* CharTexture;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};