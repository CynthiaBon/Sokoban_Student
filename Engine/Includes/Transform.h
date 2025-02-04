#pragma once

#include "libs.h"

/*
	Keywords :
	- matrix operations
	- model matrix
	- const variable
	- const method
	- reference (&)
	- reference vs pointer
	- reference vs copy
	- getter / setter
	- iterator
	- function pointer
	- callback
	- function overloading
*/

class Transform
{
public:
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	~Transform();

private :
	void constructModelMatrix();

public:
	const glm::mat4& getModelMatrix() const;

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);
	void setPosition(const float& x, const float& y, const float& z);
	void translate(const glm::vec3& position);
	void translate(const float& x, const float& y, const float& z);

	const glm::vec3& getEulerRotation() const;
	const glm::quat& getRotation() const;
	void setRotation(const glm::vec3& rotation);
	void setRotation(const float& x, const float& y, const float& z);
	void rotate(const glm::vec3& rotation);
	void rotate(const float& x, const float& y, const float& z);

	const glm::vec3 getForward() const;
	const glm::vec3 getRight() const;
	const glm::vec3 getUp() const;

	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);
	void setScale(const float& x, const float& y, const float& z);

	void addModelMatrixCallback(void(*action)(const Transform*));
	void removeModelMatrixCallback(void(*action)(const Transform*));

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_model_matrix;

	std::list<void(*)(const Transform*)> m_on_model_matrix_update;
};
