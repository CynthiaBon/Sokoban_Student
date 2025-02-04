#pragma once

#include "Shader.h"

class Texture
{
public:
	Texture(const char* filename, GLuint unit);
	Texture(GLuint texture_id, GLuint unit);
	~Texture();

	void bind();
	void unbind();

	GLuint getId();
	GLuint getUnit();

private:
	void createTexture(const char* filename);

private:
	GLuint m_id;
	GLenum m_type;
	GLuint m_unit;
};