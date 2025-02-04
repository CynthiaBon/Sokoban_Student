#include "../Includes/Camera.h"

Camera* Camera::m_main = nullptr;

Camera::Camera(GameObject* game_object) : MonoBehaviour(game_object)
{
	if (Camera::m_main == nullptr)
		setMain();
}

Camera::~Camera()
{
}

Camera* Camera::getMain()
{
	return m_main;
}

void Camera::setMain()
{
	if (m_main != nullptr)
		m_main->getGameObject()->getTransform()->removeModelMatrixCallback(updateViewMatrix);

	m_main = this;
	Transform* camera_transform = getGameObject()->getTransform();
	camera_transform->addModelMatrixCallback(updateViewMatrix);
	updateViewMatrix(camera_transform);
}

void Camera::updateViewMatrix(const Transform* camera_transform)
{
	Shader::updateAllViewMatrix(camera_transform->getPosition(), camera_transform->getForward());

}
