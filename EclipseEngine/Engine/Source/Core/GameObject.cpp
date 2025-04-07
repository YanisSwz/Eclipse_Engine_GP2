#include "GameObject.hpp"
#include "Scene.hpp"

namespace Core
{
	GameObject::GameObject(Scene* _scene, Transform* _t, std::string _name)
	{
		scene = _scene;

		if (_name == "default")
			m_name = "GameObject" + std::to_string(m_id);
		else
			m_name = _name;

		if (_t != nullptr)
		{
			transform = _t;
			transform->SetGameObject(this);
		}
		else
		{
			transform = scene->AddTransform();
			transform->SetGameObject(this);
		}

		active = true;
	}

	GameObject::~GameObject()
	{
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
		return _original.scene->CreateGameObject();
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