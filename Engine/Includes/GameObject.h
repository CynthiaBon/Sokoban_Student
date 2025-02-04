#pragma once

#include "RectTransform.h"

/*
	Keywords :
	- generic type
	- function templates
*/

class MonoBehaviour;

class GameObject
{
public:
	GameObject(const char* name, bool is_ui = false);
	~GameObject();

public:
	const char* getName();
	Transform* getTransform();

	void addComponent(MonoBehaviour* component);
	void removeComponent(MonoBehaviour* component);

	template<typename T, class = std::enable_if_t<std::is_base_of_v<MonoBehaviour, T>>>
	T* getComponent()
	{
		for (MonoBehaviour* component : m_components)
		{
			if (typeid(T) == typeid(*component))
				return dynamic_cast<T*>(component);
		}

		return nullptr;
	}

	std::list<MonoBehaviour*> getAllComponents();

private:
	Transform* m_transform;
	const char* m_name;
	std::list<MonoBehaviour*> m_components;
};
