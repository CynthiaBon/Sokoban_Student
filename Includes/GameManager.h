#pragma once

#include "../Includes/MapLoader.h"
#include <vector>
#include <random>
#include <filesystem>

using RandomRange = std::uniform_int_distribution<uint32_t>;

class GameManager : public MonoBehaviour
{
public:
	//Constructor
	GameManager(GameObject* object);
	//Destructor
	~GameManager();

private:
	//Initialization
	void loadMapList();
	void loadRandomMap();
	void findPlayerPosition();
	void reset();

	//Game loop
	void update() override;
	void inputManagement();
	void playerMovement();
	void checkVictory();

private:
	//Map
	MapLoader* m_map_loader;

	std::vector<std::string> m_map_list;
	Grid* m_grid;

	//Player
	glm::ivec2 m_player_position;
	float m_input_timer;
	float m_input_rate;

	//Random
	std::mt19937 m_rng;
};