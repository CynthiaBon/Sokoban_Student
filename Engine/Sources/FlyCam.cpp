#include "../Includes/FlyCam.h"

FlyCam::FlyCam(GameObject* object, float movement_speed, float rotation_speed)
	: MonoBehaviour(object), m_movement_speed(movement_speed), m_rotation_speed(rotation_speed)
{
	m_transform = getGameObject()->getTransform();
	GameEngine::getInstance()->setCursorState(false);
}

FlyCam::~FlyCam()
{
}

void FlyCam::update()
{
	updateRotation();
	updateMovement();
}

void FlyCam::updateMovement()
{
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_W))
		m_transform->translate(m_transform->getForward() * m_movement_speed * GameEngine::getDeltaTime());
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_S))
		m_transform->translate(-m_transform->getForward() * m_movement_speed * GameEngine::getDeltaTime());
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_A))
		m_transform->translate(m_transform->getRight() * m_movement_speed * GameEngine::getDeltaTime());
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_D))
		m_transform->translate(-m_transform->getRight() * m_movement_speed * GameEngine::getDeltaTime());
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_SPACE))
		m_transform->translate(glm::vec3(0.0f, 1.0f, 0.0f) * m_movement_speed * GameEngine::getDeltaTime());
	if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		m_transform->translate(glm::vec3(0.0f, -1.0f, 0.0f) * m_movement_speed * GameEngine::getDeltaTime());
}

void FlyCam::updateRotation()
{
	glm::vec2 cursor_delta = GameEngine::getCursorDeltaPosition();
	glm::vec3 rotation = glm::vec3(cursor_delta.y, -cursor_delta.x, 0.0f) * m_rotation_speed * GameEngine::getDeltaTime();
	m_transform->rotate(rotation);

	glm::vec3 new_rotation = m_transform->getEulerRotation();
	if (new_rotation.x < -80.0f)
	{
		new_rotation.x = -80.0f;
		m_transform->setRotation(new_rotation);
	}
	else if (new_rotation.x > 80.0f)
	{
		new_rotation.x = 80.0f;
		m_transform->setRotation(new_rotation);
	}
}
