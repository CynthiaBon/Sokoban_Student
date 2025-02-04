#pragma once

#include "../Engine/Includes/OBJLoader.h"
#include "../Engine/Includes/Material.h"

class ElementData
{
public:
	//Constructor
	ElementData(std::string mesh_path, std::string texture_path);
	//Destructor
	~ElementData();

	//Getters
	Mesh* getMesh();
	Material* getMaterial();

private:
	//Visuals
	Mesh* m_mesh;
	Texture* m_texture;
	Material* m_material;
};