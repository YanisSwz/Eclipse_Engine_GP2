#include "GameObject.hpp"

namespace Core
{
	GameObject::GameObject(std::string _name)
	{
		m_name = _name;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Destroy()
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Destroy();
		}
	}

	void GameObject::Destroy(GameObject* _obj)
	{
		if(_obj != nullptr)
		{
			_obj->Destroy();
			delete _obj;
		}
	}

	GameObject* GameObject::Instantiate(GameObject _original)
	{
		GameObject* obj = new GameObject(_original);
		return obj;
	}

	std::string GameObject::GetName() const 
	{
		return m_name;
	}

	std::string GameObject::GetName(GameObject* _obj) 
	{
		return _obj->m_name;
	}

	int GameObject::GetID() const
	{
		return m_id;
	}

	int GameObject::GetID(GameObject* _obj)
	{
		return _obj->m_id;
	}
}