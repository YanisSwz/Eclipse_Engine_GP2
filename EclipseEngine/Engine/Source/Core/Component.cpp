#include "Component.hpp"
#include "GameObject.hpp"

namespace Core
{
	void Component::SetGameObject(GameObject* _obj)
	{
		m_gameObject = _obj;
	}

	void Component::Remove()
	{
		m_gameObject->RemoveComponent(this);
		m_gameObject = nullptr;
	}
}