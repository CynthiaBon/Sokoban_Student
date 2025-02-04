#pragma once

#include "GameObject.h"
#include "Material.h"
#include "OBJLoader.h"
#include "MeshRenderer.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void setTexture(Texture* texture);
	void render(glm::vec3 camera_position);

private:
	GameObject* m_skybox;
	Material* m_skybox_material;
	MeshRenderer* m_skybox_renderer;
	Shader* m_skybox_shader;
};