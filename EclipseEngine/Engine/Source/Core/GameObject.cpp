#include "GameObject.hpp"
#include "Scene.hpp"

namespace Core
{
	meta::factory<GameObject> GameObject::factory = meta::reflect<GameObject>(hash("GameObject"))
		.data<&GameObject::SetActive, &GameObject::IsActive>(hash("IsActive"))
		.data<&GameObject::name>(hash("Name"))
		.data<&GameObject::transform>(hash("Transform"))
		.data<&GameObject::m_components>(hash("Components"));

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

	void GameObject::SetActive(bool _active)
	{
		m_active = _active;
		
		//Components 
		for (int i = 0; i < m_components.size(); ++i)
			m_components[i]->SetActive(_active);

		//Children
		for(Transform* child : transform->GetChildren())
			child->GetGameObject()->SetActive(_active);
	}
	
	SystemManager* GameObject::GetSystemManager()
	{
		return m_systemManager;
	}
}