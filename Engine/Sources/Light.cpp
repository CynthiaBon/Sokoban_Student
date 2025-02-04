#include "../Includes/Light.h"

Light* Light::m_main = nullptr;

Light::Light(GameObject* game_object, glm::vec3 color, float intensity, glm::vec3 ambiant_color) :
	MonoBehaviour(game_object), m_color(color * intensity), m_intensity(intensity), m_ambient_color(ambiant_color)
{
	if (m_main == nullptr)
		setMain();
}

Light::~Light()
{
}

void Light::setColor(glm::vec3 color, float intensity)
{
	if (intensity > 0)
		m_intensity = intensity;
	m_color = color * m_intensity;
	Shader::updateAllLightColor(m_color, false);
}

void Light::setAmbientColor(glm::vec3 ambient_color)
{
	m_ambient_color = ambient_color;
	Shader::updateAllLightColor(m_ambient_color, true);
}

Light* Light::getMain()
{
	return m_main;
}

void Light::setMain()
{

	if (m_main != nullptr)
		m_main->getGameObject()->getTransform()->removeModelMatrixCallback(updateLightDirection);

	m_main = this;
	Transform* light_transform = getGameObject()->getTransform();
	light_transform->addModelMatrixCallback(updateLightDirection);
	Shader::updateLightDirection(light_transform->getForward());

	Shader::updateAllLightColor(m_color, false);
	Shader::updateAllLightColor(m_ambient_color, true);
}

void Light::updateLightDirection(const Transform* light_transform)
{
	Shader::updateLightDirection(light_transform->getForward());
}
