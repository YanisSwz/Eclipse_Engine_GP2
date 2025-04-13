#include "GameObject.hpp"
#include "Scene.hpp"

namespace Core
{
	GameObject::GameObject(Scene* _scene, Transform* _t, std::string _name)
	{
		m_scene = _scene;

		if (_name == "default")
			name = "GameObject" + std::to_string(m_id);
		else
			name = _name;

		if (_t != nullptr)
		{
			transform = _t;
			transform->SetGameObject(this);
		}
		else
		{
			transform = m_scene->AddTransform();
			transform->SetGameObject(this);
		}

		active = true;
	}

	GameObject::~GameObject()
	{
		name.clear();
		m_components.clear();
	}

	void GameObject::Destroy()
	{
		active = false;
		transform->Destroy();
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
		//TODO: Replace with arguments
		return _original.m_scene->CreateGameObject();
	}

	std::string GameObject::GetName() const 
	{
		return name;
	}

	std::string GameObject::GetName(GameObject* _obj) 
	{
		return _obj->name;
	}
}