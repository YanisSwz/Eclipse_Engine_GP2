#include "Component.hpp"

namespace Core
{
	Component::~Component(){}

	void Component::SetGameObject(GameObject* _obj)
	{
		m_gameObject = _obj;
	}
}