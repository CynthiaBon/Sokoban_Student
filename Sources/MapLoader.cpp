#include "../Includes/MapLoader.h"

MapLoader::MapLoader()
{
	m_visuals_data = std::map<ElementType, ElementData*>
	{
		{ ElementType::None, new ElementData("", "") },
		{ ElementType::Player, new ElementData("Meshes/Player.obj", "Textures/ColorPalette.png") },
		{ ElementType::Wall, new ElementData("Meshes/Wall.obj", "Textures/ColorPalette.png") },
		{ ElementType::Box, new ElementData("Meshes/Box.obj", "Textures/ColorPalette.png") },
		{ ElementType::Target, new ElementData("Meshes/Target.obj", "Textures/ColorPalette.png") },
		{ ElementType::Ground, new ElementData("Meshes/Ground.obj", "Textures/ColorPalette.png") },
		{ ElementType::DoorClose, new ElementData("Meshes/Door.obj", "Textures/ColorPalette.png") },
		{ ElementType::DoorOpen, new ElementData("", "") },
		{ ElementType::Lever, new ElementData("Meshes/Lever.obj", "Textures/ColorPalette.png") }
	};
}

MapLoader::~MapLoader()
{
	for (auto data : m_visuals_data)
	{
		delete data.second;
	}
	m_visuals_data.clear();
}

Grid* MapLoader::loadMap(std::string filename)
{
	return nullptr;
}
