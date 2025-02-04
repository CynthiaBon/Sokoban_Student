#include "../Includes/Material.h"

Material::Material(Shader* shader) :
	Material(shader, glm::vec3(1.0f, 1.0f, 1.0f), nullptr)
{
}

Material::Material(Shader* shader, glm::vec3 color) :
	Material(shader, color, nullptr)
{
}

Material::Material(Shader* shader, glm::vec3 color, Texture* texture) :
	m_shader(shader)
{
	m_exposed_properties = shader->getShaderProperties();
	setBaseColor(color);
	setBaseTexture(texture);
}

Material::~Material()
{
}

void Material::setBaseColor(glm::vec3 color)
{
	setVector3("color", color);
}

void Material::setBaseTexture(Texture* texture)
{
	setTexture("base_texture", texture);
}

void Material::setInt(const char* name, int value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "int")
		exposed_property->value = new int(value);
}

void Material::setFloat(const char* name, float value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "float")
		exposed_property->value = new float(value);
}

void Material::setVector2(const char* name, glm::vec2 value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "vec2")
		exposed_property->value = new glm::vec2(value);
}

void Material::setVector3(const char* name, glm::vec3 value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "vec3")
		exposed_property->value = new glm::vec3(value);
}

void Material::setVector4(const char* name, glm::vec4 value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "vec4")
		exposed_property->value = new glm::vec4(value);
}

void Material::setMatrix(const char* name, glm::mat4x4 value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "mat4")
		exposed_property->value = new glm::mat4x4(value);
}

void Material::setTexture(const char* name, Texture* value)
{
	ShaderProperty* exposed_property = getExposedProperty(name);
	if (exposed_property != nullptr && exposed_property->type == "sampler2D")
	{
		exposed_property->value = value;
	}
}

void Material::sendToShader()
{
	for (ShaderProperty* exposed_property : m_exposed_properties)
	{
		void* property_value = exposed_property->value;
		const char* property_name = exposed_property->name.c_str();

		if (property_value == nullptr)
		{
			if (exposed_property->type == "sampler2D")
				m_shader->setInt((std::string("sample_") + std::string(property_name)).c_str(), 0);
			continue;
		}

		if (exposed_property->type == "int")
		{
			m_shader->setInt(property_name, *(static_cast<int*>(property_value)));
		}
		else if (exposed_property->type == "float")
		{
			m_shader->setFloat(property_name, *(static_cast<float*>(property_value)));
		}
		else if (exposed_property->type == "vec2")
		{
			m_shader->setVector2(property_name, *(static_cast<glm::vec2*>(property_value)));
		}
		else if (exposed_property->type == "vec3")
		{
			m_shader->setVector3(property_name, *(static_cast<glm::vec3*>(property_value)));
		}
		else if (exposed_property->type == "vec4")
		{
			m_shader->setVector4(property_name, *(static_cast<glm::vec4*>(property_value)));
		}
		else if (exposed_property->type == "mat4")
		{
			m_shader->setMatrix(property_name, *(static_cast<glm::mat4x4*>(property_value)));
		}
		else if (exposed_property->type == "sampler2D")
		{
			Texture* texture = static_cast<Texture*>(property_value);
			m_shader->setInt(property_name, texture->getUnit());

			m_shader->setInt((std::string("sample_") + std::string(property_name)).c_str(), 1);
			texture->bind();
		}
	}

}

void Material::unbindTextures()
{
	for (ShaderProperty* exposed_property : m_exposed_properties)
	{
		void* property_value = exposed_property->value;
		if (exposed_property->type == "sampler2D" && property_value != nullptr)
		{
			Texture* texture = static_cast<Texture*>(property_value);
			texture->unbind();
		}
	}
}

Texture* Material::getTexture()
{
	Texture* texture = nullptr;

	for (ShaderProperty* exposed_property : m_exposed_properties)
	{
		if (exposed_property->type == "sampler2D" && exposed_property->name == "base_texture")
		{
			texture = static_cast<Texture*>(exposed_property->value);
			return texture;
		}
	}

	return texture;
}

Shader* Material::getShader()
{
	return m_shader;
}

ShaderProperty* Material::getExposedProperty(std::string property_name)
{
	for (int i = 0; i < m_exposed_properties.size(); i++)
	{
		if (m_exposed_properties[i]->name == property_name)
			return m_exposed_properties[i];
	}

	return nullptr;
}
