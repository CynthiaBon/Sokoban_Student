#include "../Includes/Transform.h"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
	m_position(position), m_rotation(rotation), m_scale(scale)
{
	m_on_model_matrix_update = std::list<void(*)(const Transform*)>();
	constructModelMatrix();
}

Transform::~Transform()
{
	m_on_model_matrix_update.clear();
}

void Transform::constructModelMatrix()
{
	m_model_matrix = glm::mat4(1.0f);
	m_model_matrix = glm::translate(m_model_matrix, m_position);
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_model_matrix = glm::scale(m_model_matrix, m_scale / 100.0f);

	for (std::list<void(*)(const Transform*)>::iterator i = m_on_model_matrix_update.begin(); i != m_on_model_matrix_update.end(); i++)
	{
		(*i)(this);
	}
}

const glm::mat4& Transform::getModelMatrix() const
{
	return m_model_matrix;
}

const glm::vec3& Transform::getPosition() const
{
	return m_position;
}

void Transform::setPosition(const glm::vec3& position)
{
	m_position = position;
	constructModelMatrix();
}

void Transform::setPosition(const float& x, const float& y, const float& z)
{
	setPosition(glm::vec3(x, y, z));
}

void Transform::translate(const glm::vec3& position)
{
	setPosition(m_position + position);
}

void Transform::translate(const float& x, const float& y, const float& z)
{
	translate(glm::vec3(x, y, z));
}

const glm::vec3& Transform::getEulerRotation() const
{
	return m_rotation;
}

const glm::quat& Transform::getRotation() const
{
	return glm::quat(glm::radians(m_rotation));
}

void Transform::setRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
	constructModelMatrix();
}

void Transform::setRotation(const float& x, const float& y, const float& z)
{
	setRotation(glm::vec3(x, y, z));
}

void Transform::rotate(const glm::vec3& rotation)
{
	glm::vec3 newRotation = m_rotation + rotation;
	newRotation.x = fmod(newRotation.x, 360.0f);
	newRotation.y = fmod(newRotation.y, 360.0f);
	newRotation.z = fmod(newRotation.z, 360.0f);
	setRotation(newRotation);
}

void Transform::rotate(const float& x, const float& y, const float& z)
{
	rotate(glm::vec3(x, y, z));
}

const glm::vec3 Transform::getForward() const
{
	glm::vec3 world_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::quat quatRotation = glm::quat(glm::radians(m_rotation));
	return quatRotation * world_forward;
}

const glm::vec3 Transform::getRight() const
{
	glm::vec3 world_right = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::quat quatRotation = glm::quat(glm::radians(m_rotation));
	return quatRotation * world_right;
}

const glm::vec3 Transform::getUp() const
{
	glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat quatRotation = glm::quat(glm::radians(m_rotation));
	return quatRotation * world_up;
}

const glm::vec3& Transform::getScale() const
{
	return m_scale;
}

void Transform::setScale(const glm::vec3& scale)
{
	m_scale = scale;
	constructModelMatrix();
}

void Transform::setScale(const float& x, const float& y, const float& z)
{
	setScale(glm::vec3(x, y, z));
}

void Transform::addModelMatrixCallback(void(*action)(const Transform*))
{
	m_on_model_matrix_update.push_back(action);
}

void Transform::removeModelMatrixCallback(void(*action)(const Transform*))
{
	m_on_model_matrix_update.remove(action);
}
