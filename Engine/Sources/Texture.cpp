#include "../Includes/Texture.h"

Texture::Texture(const char* filename, GLuint unit) : m_type(GL_TEXTURE_2D), m_unit(unit)
{
	createTexture(filename);
}

Texture::Texture(GLuint texture_id, GLuint unit) : m_id(texture_id), m_type(GL_TEXTURE_2D), m_unit(unit)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(m_type, m_id);
}

void Texture::unbind()
{
	glBindTexture(m_type, 0);
}

GLuint Texture::getId()
{
	return m_id;
}

GLuint Texture::getUnit()
{
	return m_unit;
}

void Texture::createTexture(const char* filename)
{
	int image_width = 0;
	int image_height = 0;
	unsigned char* sprite = SOIL_load_image(filename, &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	if (sprite)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		SOIL_free_image_data(sprite);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		m_id = 0;
		std::cerr << "MATERIAL ERROR: " << filename << " did not load\n";
	}
}
