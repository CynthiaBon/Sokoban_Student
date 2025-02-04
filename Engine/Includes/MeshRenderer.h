#pragma once

#include "MonoBehaviour.h"
#include "Mesh.h"
#include "Material.h"

/*
	Keywords :
	- inheritance
*/

class MeshRenderer : public MonoBehaviour
{
public:
	MeshRenderer(GameObject* game_object, Mesh* mesh, Material* material);
	~MeshRenderer();

	virtual void render();

	Mesh* getMesh();
	void setMesh(Mesh* renderer);

	Material* getMaterial();
	void setMaterial(Material* material);

private:
	Mesh* m_mesh;
	Material* m_material;
};