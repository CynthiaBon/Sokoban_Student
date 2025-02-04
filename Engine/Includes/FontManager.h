#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H
#include "Character.h"

class FontManager
{
public:
	~FontManager();

	Character getCharacter(char c);
	static FontManager* getInstance();

	FontManager(FontManager& other) = delete;
	void operator=(const FontManager&) = delete;

private:
	FontManager();

	void initializeFreeType();
	void loadCharacters();

private:
	FT_Library m_ft;
	FT_Face m_face;

	std::map<unsigned char, Character> m_characters;

	static FontManager* m_instance;
};