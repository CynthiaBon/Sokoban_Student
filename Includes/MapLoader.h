#pragma once

#include "Grid.h"
#include <fstream>

class MapLoader
{
public:
	//Constructor
	MapLoader();
	//Destructor
	~MapLoader();

	//Map
	Grid* loadMap(std::string filename);

private:
	//Visuals data
	std::map<ElementType, ElementData*> m_visuals_data;
};