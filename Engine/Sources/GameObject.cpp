#include "../Includes/GameObject.h"

GameObject::GameObject(const char* name, bool is_ui) :
	m_name(name)
{
	if (!is_ui)
		m_transform = new Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	else
		m_transform = RectTransform::castBase(new RectTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f)));
	m_components = std::list<MonoBehaviour*>();
}

GameObject::~GameObject()
{
	/*delete m_transform;*/
	/*m_components.clear();*/
}

const char* GameObject::getName()
{
	return m_name;
}

Transform* GameObject::getTransform()
{
	return m_transform;
}

void GameObject::addComponent(MonoBehaviour* component)
{
	m_components.push_back(component);
}

void GameObject::removeComponent(MonoBehaviour* component)
{
	m_components.remove(component);
	delete component;
}

std::list<MonoBehaviour*> GameObject::getAllComponents()
{
	return m_components;
}
