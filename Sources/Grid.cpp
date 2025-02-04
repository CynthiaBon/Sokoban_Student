#include "../Includes/Grid.h"

Grid::Grid(std::string size, std::map<ElementType, ElementData*> visuals_data)
{
	m_visuals_data = visuals_data;
}

void Grid::createEmptyGrid(std::string size)
{
}

Grid::~Grid()
{
}

void Grid::setElement(int pos_x, int pos_y, ElementType type)
{
}

void Grid::copyGridToMemory()
{
}

void Grid::reset()
{
}

glm::ivec2 Grid::getSize()
{
	return glm::ivec2(0.0f);
}

ElementType Grid::getElementAt(int x, int y)
{
	return ElementType::None;
}

ElementType Grid::getMemoryElementAt(int x, int y)
{
	return ElementType::None;
}

bool Grid::moveElement(glm::ivec2 element_position, glm::ivec2 direction)
{
	return false;
}

bool Grid::isPositionValid(glm::ivec2 position)
{
	return false;
}

bool Grid::isWall(ElementType type)
{
	return false;
}

bool Grid::isMoveable(ElementType type)
{
	return false;
}

void Grid::useLever()
{
}
