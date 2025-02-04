#include "../Includes/FontManager.h"

FontManager* FontManager::m_instance = nullptr;

FontManager::FontManager()
{
	try
	{
		initializeFreeType();
		loadCharacters();
		FT_Done_Face(m_face);
		FT_Done_FreeType(m_ft);
	}
	catch (const std::exception& exception)
	{
		std::cerr << "FONT ERROR: " << exception.what() << "\n";
	}
}

FontManager::~FontManager()
{
}

FontManager* FontManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new FontManager();

	return m_instance;
}

void FontManager::initializeFreeType()
{
	if (FT_Init_FreeType(&m_ft))
		throw std::exception("FreeType did not load");

	if (FT_New_Face(m_ft, "Fonts/Roboto-Regular.ttf", 0, &m_face))
		throw std::exception("Font did not load");

	FT_Set_Pixel_Sizes(m_face, 0, 48);
}

Character FontManager::getCharacter(char c)
{
	return m_characters[c];
}

void FontManager::loadCharacters()
{
	m_characters = std::map<unsigned char, Character>();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
		{
			std::cerr << "FONT ERROR: failed to load glyph\n";
			continue;
		}

		GLuint width = m_face->glyph->bitmap.width;
		GLuint height = m_face->glyph->bitmap.rows;

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		Character character = {
			new Texture(texture, 0),
			glm::ivec2(width, height),
			glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
			m_face->glyph->advance.x
		};

		m_characters.insert(std::pair<unsigned char, Character>(c, character));
	}
}
