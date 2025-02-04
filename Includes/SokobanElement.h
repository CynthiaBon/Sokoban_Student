#pragma once

#include "ElementType.h"
#include "../Engine/Includes/GameEngine.h"

class SokobanElement
{
public:
	//Constructor
	SokobanElement();
	//Destructor
	~SokobanElement();

	//Initialization
	void initialize(int x, int y, Mesh* ground_mesh, Material* ground_material);
	//Getter
	ElementType getType();
	//Setter
	void setType(ElementType type, Mesh* mesh, Material* material);

private:
	//Type
	ElementType m_type;

	//Visuals
	GameObject* m_object;
	MeshRenderer* m_renderer;

	GameObject* m_ground_object;
	MeshRenderer* m_ground_renderer;
};