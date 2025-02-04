#pragma once

#include "Texture.h"

/*
	Keywords :
	- function overloading
	- type casting
	- void pointer
*/

class Material
{
public:
	Material(Shader* shader);
	Material(Shader* shader, glm::vec3 color);
	Material(Shader* shader, glm::vec3 color, Texture *texture);
	~Material();

	void setBaseColor(glm::vec3 color);
	void setBaseTexture(Texture* texture);

	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVector2(const char* name, glm::vec2 value);
	void setVector3(const char* name, glm::vec3 value);
	void setVector4(const char* name, glm::vec4 value);
	void setMatrix(const char* name, glm::mat4x4 value);
	void setTexture(const char* name, Texture* value);

	Shader* getShader();
	void sendToShader();
	void unbindTextures();
	Texture* getTexture();

private:
	ShaderProperty* getExposedProperty(std::string property_name);

private:
	Shader* m_shader;
	std::vector<ShaderProperty*> m_exposed_properties;
};
