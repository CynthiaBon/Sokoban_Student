#include "../Includes/GameManager.h"

GameManager::GameManager(GameObject* object) : MonoBehaviour(object)
{
	m_rng = std::mt19937();
	m_rng.seed((unsigned)time(0));

	loadMapList();

	Camera::getMain()->getGameObject()->getTransform()->setRotation(-60.0f, 0.0f, 0.0f);

	m_input_rate = 0.3f;
	m_input_timer = m_input_rate;
}

GameManager::~GameManager()
{
}

void GameManager::loadMapList()
{
	const std::string path_to_maps = "Maps";
	m_map_list = std::vector<std::string>();

	for (auto file : std::filesystem::directory_iterator(path_to_maps))
	{
		m_map_list.push_back(file.path().string());
	}
}

void GameManager::loadRandomMap()
{
}

void GameManager::findPlayerPosition()
{
}

void GameManager::update()
{
}

void GameManager::inputManagement()
{
}

void GameManager::playerMovement()
{
}

void GameManager::reset()
{
}

void GameManager::checkVictory()
{
}
