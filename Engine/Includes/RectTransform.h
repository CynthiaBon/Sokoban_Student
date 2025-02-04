#pragma once

#include "Transform.h"

class RectTransform : private Transform
{
public:
	RectTransform(const glm::vec2& position, const float rotation, const glm::vec2& size);
	~RectTransform();

	const glm::vec2& getPosition() const;
	void setPosition(const glm::vec2& position);
	void setPosition(const float& x, const float& y);

	const float& getRotation() const;
	void setRotation(const float& z);

	const glm::vec2& getSize() const;
	void setSize(const glm::vec2& size);
	void setSize(const float& size_x, const float& size_y);

	const int& getOrderInLayer() const;
	void setOrderInLayer(const int& order_in_layer);

	static RectTransform* castToRect(Transform* transform);
	static Transform* castBase(RectTransform* transform);

private:
	glm::vec2 m_size;
	int m_order_in_layer;
};
