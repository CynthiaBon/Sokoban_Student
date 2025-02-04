#include "../Includes/MonoBehaviour.h"

MonoBehaviour::MonoBehaviour(GameObject* game_object)
{
	m_game_object = game_object;
	m_active = true;
	m_game_object->addComponent(this);
}

GameObject* MonoBehaviour::getGameObject()
{
	return m_game_object;
}

void MonoBehaviour::setActive(bool value)
{
	if (value == m_active)
		return;

	m_active = value;
	if (m_active)
		onEnable();
	else
		onDisable();
}

bool MonoBehaviour::isActive()
{
	return m_active;
}

void MonoBehaviour::update() { }

void MonoBehaviour::onEnable() { }

void MonoBehaviour::onDisable() { }
