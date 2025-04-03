#include "GameObject.hpp"
#include "Scene.hpp"

namespace Core
{
	GameObject::GameObject()
	{
		transform = scene->AddTransform();
	}

	GameObject::GameObject(Scene* _scene, std::string _name, Transform* _t)
	{
		scene = _scene;
		m_name = _name;
		if(_t != nullptr)
			transform = _t;
		else 
			transform = scene->AddTransform();
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
		destroyed = true;
	}

	void GameObject::Destroy(GameObject* _obj)
	{
		_obj->Destroy();
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
}