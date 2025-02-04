#pragma once

#include "MonoBehaviour.h"
#include "GameEngine.h"

class FlyCam : public MonoBehaviour
{
public:
	FlyCam(GameObject* object, float movement_speed, float rotation_speed);
	~FlyCam();

protected:
	void update() override;

private:
	void updateMovement();
	void updateRotation();

private:
	float m_movement_speed;
	float m_rotation_speed;
	Transform* m_transform;
};