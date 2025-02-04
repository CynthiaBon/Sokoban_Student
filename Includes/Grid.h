#pragma once

#include <sstream>
#include <iostream>
#include "SokobanElement.h"
#include "ElementData.h"
#include <map>
#include "../Engine/Includes/Debug.h"

class Grid
{
public:
	//Constructor
	Grid(std::string size, std::map<ElementType, ElementData*> visuals_data);
	//Destructor
	~Grid();

	//Map
	void copyGridToMemory();
	void reset();
	void setElement(int pos_x, int pos_y, ElementType type);
	bool moveElement(glm::ivec2 element_position, glm::ivec2 direction);

	//Getters
	glm::ivec2 getSize();
	ElementType getElementAt(int x, int y);
	ElementType getMemoryElementAt(int x, int y);

private:
	//Map
	void createEmptyGrid(std::string size);
	bool isPositionValid(glm::ivec2 position);
	bool isWall(ElementType type);
	bool isMoveable(ElementType type);
	void useLever();

private:
	//Map
	SokobanElement** m_grid;
	ElementType** m_memory_grid;

	int m_size_x;
	int m_size_y;

	//Visuals data
	std::map<ElementType, ElementData*> m_visuals_data;
};