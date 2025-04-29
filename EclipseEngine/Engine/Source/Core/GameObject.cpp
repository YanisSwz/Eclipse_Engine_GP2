#include "GameObject.hpp"
#include "Scene.hpp"

namespace Core
{
	meta::factory<GameObject> GameObject::factory = meta::reflect<GameObject>(m_hash("GameObject"))
		.data<&GameObject::SetActive, &GameObject::IsActive>(m_hash("IsActive"))
		.data<&GameObject::name>(m_hash("Name"))
		.data<&GameObject::transform>(m_hash("Transform"))
		.data<&GameObject::m_components>(m_hash("Components"));

	GameObject::GameObject(SystemManager* _manager, Transform* _t, std::string _name)
	{
		m_systemManager = _manager;

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
			transform = m_systemManager->AddTransform();
			transform->SetGameObject(this);
		}

		m_active = true;
	}

	GameObject::~GameObject()
	{
		name.clear();
		m_components.clear();
	}

	void GameObject::Destroy()
	{
		m_active = false;
		transform->Destroy();
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Destroy();
		}
		m_destroyed = true;
	}

	void GameObject::Destroy(GameObject* _obj)
	{
		_obj->Destroy();
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