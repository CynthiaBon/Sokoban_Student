#pragma once

#include "MonoBehaviour.h"
#include "Shader.h"

/*
	Keywords :
	- inheritance
	- static
	- default parameter
*/

class Light : public MonoBehaviour
{
public:
	Light(GameObject* game_object, glm::vec3 color, float intensity, glm::vec3 ambiant_color);
	~Light();

	void setColor(glm::vec3 color, float intensity = -1.0f);
	void setAmbientColor(glm::vec3 ambient_color);

	static Light* getMain();
	void setMain();

private:
	static void updateLightDirection(const Transform* light_transform);

private:
	glm::vec3 m_color;
	float m_intensity;
	glm::vec3 m_ambient_color;

	static Light* m_main;
};