#pragma once

#include "GameObject.h"

/*
	Keywords :
	- virtual / override
	- protected
*/

class MonoBehaviour
{
public:
	MonoBehaviour(GameObject* game_object);
	virtual ~MonoBehaviour() = default;

	GameObject* getGameObject();
	void setActive(bool value);
	bool isActive();
	virtual void update();

protected:
	virtual void onEnable();
	virtual void onDisable();
	GameObject* m_game_object;

private:
	bool m_active;
};