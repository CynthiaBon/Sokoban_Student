#pragma once

#include "MonoBehaviour.h"
#include "Material.h"

class SpriteRenderer : public MonoBehaviour
{
public:
	SpriteRenderer(GameObject* game_object, Material* material);
	~SpriteRenderer();

	Material* getMaterial();
	void setMaterial(Material* material);

	virtual void render(GLuint& vbo);

protected:
	Material* m_material;
};