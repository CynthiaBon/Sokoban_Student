#include "../Includes/RectTransform.h"

RectTransform::RectTransform(const glm::vec2& position, const float rotation, const glm::vec2& size) :
	Transform(glm::vec3(position.x, position.y, 0.0f), glm::vec3(0.0f, 0.0f, rotation), glm::vec3(1.0f)), m_size(size), m_order_in_layer(0)
{
}

RectTransform::~RectTransform()
{
}

const glm::vec2& RectTransform::getPosition() const
{
	return Transform::getPosition();
}

void RectTransform::setPosition(const glm::vec2& position)
{
	Transform::setPosition(position.x, position.y, 0.0f);
}

void RectTransform::setPosition(const float& x, const float& y)
{
	Transform::setPosition(x, y, 0.0f);
}

const float& RectTransform::getRotation() const
{
	return Transform::getEulerRotation().z;
}

void RectTransform::setRotation(const float& z)
{
	Transform::setRotation(0.0f, 0.0f, z);
}

const glm::vec2& RectTransform::getSize() const
{
	return m_size;
}

void RectTransform::setSize(const glm::vec2& size)
{
	m_size = size;
}

void RectTransform::setSize(const float& size_x, const float& size_y)
{
	setSize(glm::vec2(size_x, size_y));
}

const int& RectTransform::getOrderInLayer() const
{
	return m_order_in_layer;
}

void RectTransform::setOrderInLayer(const int& order_in_layer)
{
	m_order_in_layer = order_in_layer;
}

RectTransform* RectTransform::castToRect(Transform* transform)
{
	return static_cast<RectTransform*>(transform);
}

Transform* RectTransform::castBase(RectTransform* transform)
{
	return static_cast<Transform*>(transform);
}
